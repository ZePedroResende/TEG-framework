import json

if __name__ == '__main__':
    with open("../parser/teg.json") as file:
        with open("../parser/teg.h", 'w+') as out:
            out.seek(0)
            data = json.load(file)
            functions = list(data.keys())
            out.write("enum TEG { SUCCESS, FAIL")
            if len(functions) > 0:
                out.write(',')
                out.write(','.join(functions))
            out.write("};")
            out.truncate()
