
import PythonLabelFileGenerator
import unittest

from PythonLabelFileGenerator import * 

class TestXXX(unittest.TestCase):
    def test(self):
        print("XXX")
        self.assertEqual(1.0, 1.0)
        generator = PythonLabelFileGenerator
        generator.read("")


        
if __name__ == '__main__':
    unittest.main()