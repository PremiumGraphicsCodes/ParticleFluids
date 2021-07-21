class LabeledLabel:
    def __init__(self):
        self.title = ""
        self.value = ""

class PythonLabelFileGenerator:
    def __init__(self):
        self.lls = []

    def read(self,file_path):
        print("XXX")
        f = open(file_path, 'r')
        line = f.readline()
        line = line.rstrip('\n')
        while line :
            print(line)
            lines = line.split()
            if len(line) >= 3:
                if lines[0] == 'PublicLabel' :
                    ll = LabeledLabel
                    ll.title = lines[1]
                    assert(lines[2] == '=')
                    ll.value = lines[3]
                    self.lls.append(ll)

            line = f.readline()
        f.close()
