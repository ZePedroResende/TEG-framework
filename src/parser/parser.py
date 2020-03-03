from __future__ import print_function
from itertools import chain
from collections.abc import Iterable
import json
import sys
import re

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
#
sys.path.extend(['.', '..'])

from pycparser import parse_file, c_ast
from pycparser.plyparser import Coord


RE_CHILD_ARRAY = re.compile(r'(.*)\[(.*)\]')
RE_INTERNAL_ATTR = re.compile('__.*__')


class CJsonError(Exception):
    pass


def memodict(fn):
    """ Fast memoization decorator for a function taking a single argument """
    class memodict(dict):
        def __missing__(self, key):
            ret = self[key] = fn(key)
            return ret
    return memodict().__getitem__


@memodict
def child_attrs_of(klass):
    """
    Given a Node class, get a set of child attrs.
    Memoized to avoid highly repetitive string manipulation
    """
    non_child_attrs = set(klass.attr_names)
    all_attrs = set([i for i in klass.__slots__ if not RE_INTERNAL_ATTR.match(i)])
    return all_attrs - non_child_attrs


def to_dict(node):
    """ Recursively convert an ast into dict representation. """
    klass = node.__class__

    result = {}

    # Metadata
    result['_nodetype'] = klass.__name__

    # Local node attributes
    for attr in klass.attr_names:
        result[attr] = getattr(node, attr)

    # Coord object
    if node.coord:
        result['coord'] = str(node.coord)
    else:
        result['coord'] = None

    # Child attributes
    for child_name, child in node.children():
        # Child strings are either simple (e.g. 'value') or arrays (e.g. 'block_items[1]')
        match = RE_CHILD_ARRAY.match(child_name)
        if match:
            array_name, array_index = match.groups()
            array_index = int(array_index)
            # arrays come in order, so we verify and append.
            result[array_name] = result.get(array_name, [])
            if array_index != len(result[array_name]):
                raise CJsonError('Internal ast error. Array {} out of order. '
                    'Expected index {}, got {}'.format(
                    array_name, len(result[array_name]), array_index))
            result[array_name].append(to_dict(child))
        else:
            result[child_name] = to_dict(child)

    # Any child attributes that were missing need "None" values in the json.
    for child_attr in child_attrs_of(klass):
        if child_attr not in result:
            result[child_attr] = None

    return result


def to_json(node, **kwargs):
    """ Convert ast node to json string """
    return json.dumps(to_dict(node), **kwargs)


def file_to_dict(filename):
    """ Load C file into dict representation of ast """
    ast = parse_file(filename, use_cpp=True)
    return to_dict(ast)


def file_to_json(filename, **kwargs):
    """ Load C file into json string representation of ast """
    ast = parse_file(filename, use_cpp=True)
    return to_json(ast, **kwargs)


def _parse_coord(coord_str):
    """ Parse coord string (file:line[:column]) into Coord object. """
    if coord_str is None:
        return None

    vals = coord_str.split(':')
    vals.extend([None] * 3)
    filename, line, column = vals[:3]
    return Coord(filename, line, column)


def _convert_to_obj(value):
    """
    Convert an object in the dict representation into an object.
    Note: Mutually recursive with from_dict.
    """
    value_type = type(value)
    if value_type == dict:
        return from_dict(value)
    elif value_type == list:
        return [_convert_to_obj(item) for item in value]
    else:
        # String
        return value


def from_dict(node_dict):
    """ Recursively build an ast from dict representation """
    class_name = node_dict.pop('_nodetype')

    klass = getattr(c_ast, class_name)

    # Create a new dict containing the key-value pairs which we can pass
    # to node constructors.
    objs = {}
    for key, value in node_dict.items():
        if key == 'coord':
            objs[key] = _parse_coord(value)
        else:
            objs[key] = _convert_to_obj(value)

    # Use keyword parameters, which works thanks to beautifully consistent
    # ast Node initializers.
    return klass(**objs)


def from_json(ast_json):
    return from_dict(json.loads(ast_json))

def cond(cond_tree):
    if(cond_tree["_nodetype"] == "ID"):
        return cond_tree["name"]

    if(cond_tree["_nodetype"] == "Constant"):
        return cond_tree["value"]

    if(cond_tree["_nodetype"] == "Compound"):
        return list(map(lambda x: cond(x), cond_tree["block_items"]))

    if(cond_tree["_nodetype"] == "UnaryOp"):
        op = cond_tree["op"]
        expr =  cond(cond_tree["expr"])
        return op + "(" + expr + ")"

    if(cond_tree["_nodetype"] == "BinaryOp"):
        left = cond_tree["left"]
        op = cond_tree["op"]
        right =  cond_tree["right"]
        return cond(left) + op + cond(right)

    if(cond_tree["_nodetype"] == "Return"):
        return [['True',cond_tree["expr"]["name"]]]


    if(cond_tree["_nodetype"] == "If"):
        condition = cond(cond_tree["cond"])
        true = []
        false = []

        if cond_tree["iftrue"] is not None :
            true = list(map(lambda r: update_cond_list_true(r, condition), cond(cond_tree["iftrue"])))
        if cond_tree["iffalse"] is not None :
            false = list(map(lambda r: update_cond_list_false(r, condition), cond(cond_tree["iffalse"])))

        result = true + false
        return result

def update_cond_list_true(list_cond, condition):
    if any(isinstance(el, list) for el in list_cond):
        for item in list_cond:
            update_cond_list_true(item, condition)
        return list_cond

    list_cond[0] = list_cond[0] + " && (" + condition + ")"
    return list_cond

def update_cond_list_false(list, condition):
    list[0] = list[0] + " && !(" + condition + ")"
    return list

def find_func(ast):
    dic = {}
    for item in ast['ext'] :
        if item["_nodetype"] == "FuncDef" :
            print(item["decl"]["name"])
            if list(map(lambda arg: (arg["name"], arg["type"]["type"]["names"][0]),item["decl"]["type"]["args"]["params"])) == [('thread_id', 'int'), ('data', 'Data')] :
                a = list(filter(lambda item: item["_nodetype"] in ["If","Return"],item["body"]["block_items"]))
                print(list(map(lambda x: cond(x), a)))
                for (p1,p2) in pairwise( list(flatten(list(map(lambda x: cond(x), a))))) :
                    value = dic.get(item["decl"]["name"],{})
                    value.update({p2:p1})
                    dic.update({item["decl"]["name"]: value })


    print(json.dumps(dic, sort_keys=True, indent=4))
    with open('teg.json', 'w+') as outfile:
        json.dump(dic, outfile, sort_keys=True, indent=4)



def flatten(l):
    for el in l:
        if isinstance(el, Iterable) and not isinstance(el, (str, bytes)):
            yield from flatten(el)
        else:
            yield el

def pairwise(iterable):
    a = iter(iterable)
    return zip(a, a)


#------------------------------------------------------------------------------
if __name__ == "__main__":
    if len(sys.argv) > 1:
        # Some test code...
        # Do trip from C -> ast -> dict -> ast -> json, then print.
        ast_dict = file_to_dict(sys.argv[1])
        find_func(ast_dict)
        ast = from_dict(ast_dict)
        #print(to_json(ast, sort_keys=True, indent=4))
    else:
        print("Please provide a filename as argument")
