from z3 import *
import re
import json

if __name__ == '__main__':
    with open("../parser/teg.json") as file:
        data = json.load(file)
        for (k,v) in data.items():
            s = Solver()
            a = Bool('a')
            b = Int('b')
            x = simplify(And(a, b>1))
            print(x)

            for (prop, cond) in v.items() :

                strings = re.findall(r"\b(?!True)[a-zA-Z]+",cond)
                for item in strings :
                    exec("%s = Int('%s')" % (item,item))

                condition = ('solve('+ cond+ ')')
                print(condition)
                eval(condition)

            if not s.check():
                print("Failed")
