
import CrystalPython
import unittest

from CrystalPython import add, POINT, Vector3df, Vector3dd, create_command, set_arg, get_result_int
from CrystalPython import execute_command, create_vdb_command


print('doc=', CrystalPython.__doc__)

class TestVector3df(unittest.TestCase):
    def test(self):
        v = Vector3df(1.0, 2.0, 3.0)
        self.assertEqual(1.0, v.x)
        self.assertEqual(2.0, v.y)
        self.assertEqual(3.0, v.z)

class TestVector3dd(unittest.TestCase):
    def test(self):
        v = Vector3dd(1.0,2.0,3.0)
        self.assertEqual(1.0, v.x)
        self.assertEqual(2.0, v.y)
        self.assertEqual(3.0, v.z)

class PhysicsSolverCreateCommandTest(unittest.TestCase):
    def test(self):
        create_command("PhysicsSolverCreateCommand")
        execute_command()
        newId = get_result_int("NewId")
        self.assertEqual(1, newId)
        #factory = PhysicsCommandFactory;
        #factory.create()

class VDBInitCommandTest(unittest.TestCase):
    def test(self):
        create_vdb_command("VDBInit")
        execute_command()

if __name__ == '__main__':
    unittest.main()

#CrystalPython.call("PhysicsSolverCreateCommand");