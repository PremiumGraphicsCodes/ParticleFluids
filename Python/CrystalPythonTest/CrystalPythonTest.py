
import CrystalPython
import unittest
import os
import physics_labels
import vdb_labels

from CrystalPython import *

print('doc=', CrystalPython.__doc__)

class PhysicsCommand :
    def create_solver(self) :
        create_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command()
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
        return newId

class VDBCommand :
    def init(self) :
        create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
        isOk = execute_command()
        return isOk

    def read_vdb_file(self, filepath) :
        create_vdb_command(vdb_labels.VDBFileReadLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileReadLabels.FilePathLabel, filepath)
        execute_command()
        newIds = get_result_int_vector(vdb_labels.VDBFileReadLabels.NewIdLabel)
        return newIds

    def write_vdb_file(self, filepath, particleSystemIds, volumeIds) :
        create_vdb_command(vdb_labels.VDBFileWriteLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileWriteLabels.FilePathLabel, filepath)
        set_arg_int_vector(vdb_labels.VDBFileWriteLabels.ParticleSystemIdsLabel, particleSystemIds)
        set_arg_int_vector(vdb_labels.VDBFileWriteLabels.VDBVolumeIdsLabel, volumeIds);
        execute_command()

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
        physics = PhysicsCommand()
        newId = physics.create_solver()
        self.assertEqual(1, newId)

class VDBCommand_test(unittest.TestCase):
    def setUp(self):
        self.vdb = VDBCommand()
        self.vdb.init()

    def test_read_vdb_file(self):
        newIds = self.vdb.read_vdb_file("./source_river.vdb")
        print(newIds)
        self.vdb.write_vdb_file("test_write.vdb", newIds, [])
#        self.assertEqual(1, newId)


if __name__ == '__main__':
    unittest.main()

#CrystalPython.call("PhysicsSolverCreateCommand");