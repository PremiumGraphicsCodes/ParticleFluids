
import PythonLabelFileGenerator
import unittest

from PythonLabelFileGenerator import * 

class TestXXX(unittest.TestCase):
    def test(self):
        self.assertEqual(1.0, 1.0)
        generator = PythonLabelFileGenerator()
        generator.read("./labels.h")
        generator.write("./labels.py")

        
if __name__ == '__main__':
    unittest.main()