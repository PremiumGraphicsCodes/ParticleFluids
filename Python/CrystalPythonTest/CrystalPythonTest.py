
import CrystalPython
import unittest
import os
import physics_labels
import vdb_labels

from CrystalPython import *

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
        create_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command()
        self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
        self.assertEqual(1, newId)
        #factory = PhysicsCommandFactory;
        #factory.create()

class VDBInitCommandTest(unittest.TestCase):
    def test(self):
        create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
        isOk = execute_command()
        self.assertTrue(isOk)

class VDBFileImportCommandTest(unittest.TestCase):
    def test(self):
#        path = os.getcwd()
#        print(path)
        create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
        isOk = execute_command()
        self.assertTrue(isOk)

        create_vdb_command(vdb_labels.VDBFileReadLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileReadLabels.FilePathLabel, "./source_river.vdb")
        execute_command()
        newIds = get_result_int_vector(vdb_labels.VDBFileReadLabels.NewIdLabel)
        print(newIds)
#        self.assertEqual(1, newId)


if __name__ == '__main__':
    unittest.main()

#CrystalPython.call("PhysicsSolverCreateCommand");