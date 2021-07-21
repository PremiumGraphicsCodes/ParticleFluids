
class PythonLabelFileGenerator:
    def read(file_path):
        print("XXX")
        f = open(file_path, 'r')
        line = f.readline()
        while line :
            print(line)
            line = f.readline()
        f.close()
