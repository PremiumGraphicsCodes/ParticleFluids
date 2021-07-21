import os
import glob

class LabeledLabel:
    def __init__(self):
        self.title = ""
        self.value = ""

class LabledLabelGroup:
    def __init__(self):
        self.name = ""
        self.lls = []

    def add(self, ll):
        self.lls.append(ll)

class PythonLabelFileGenerator:
    def __init__(self):
        self.groups = []

    def read_all_files(self, dir_path) :
        files = glob.glob(dir_path)
        for file in files:
            print(file)
            group = self.read(file)
            self.groups.append(group)

    def read(self,file_path):
        f = open(file_path, 'r')
        file_name = os.path.basename(file_path)
        basename_without_ext = os.path.splitext(os.path.basename(file_name))[0]
        group = LabledLabelGroup()
        group.name = basename_without_ext
        line = f.readline()
        line = line.rstrip('\n')
        while line :
            print(line)
            lines = line.split()
            if len(line) >= 3:
                if lines[0] == 'PublicLabel' :
                    ll = LabeledLabel()
                    ll.title = lines[1]
                    assert(lines[2] == '=')
                    ll.value = lines[3].rstrip(';')
                    group.add(ll)

            line = f.readline()
        f.close()
        return group

    def write(self,file_path):
        f = open(file_path, 'w')
        for group in self.groups :
            f.write("class " + group.name + ":\n")
            for ll in group.lls:
                f.write("   " + ll.title)
                f.write('=')
                f.write(ll.value)
                f.write('\n') 
        f.close()
