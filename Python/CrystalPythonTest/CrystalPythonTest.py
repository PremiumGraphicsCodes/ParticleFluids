
import CrystalPython
import unittest
import os
import scene_labels
import physics_labels
import vdb_labels

from CrystalPython import *

print('doc=', CrystalPython.__doc__)

class SceneCommand :
    def __init__(self, world) :
        self.world = world

    def clear(self, layer) :
        create_scene_command(scene_labels.ClearLabels.CommandNameLabel);
        set_arg_int(scene_labels.ClearLabels.LayerLabel, layer);
        return execute_command(self.world);

    def delete(self, id, isItem):
        create_scene_command(scene_labels.DeleteLabels.CommandNameLabel)
        set_arg_int(scene_labels.DeleteLabels.IdLabel, id)
        set_arg_bool(scene_labels.DeleteLabels.IsItemLabel, isItem)
        return execute_command(self.world)

class PhysicsCommand :
    def __init__(self, world) :
        self.world = world

    def create_solver(self) :
        create_physics_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command(self.world)
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
        return newId

class VDBCommand :
    def __init__(self, world) :
        self.world = world
 #      create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
 #       isOk = execute_command(self.world)

    def init(self) :
#        self.world = world
        create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
        isOk = execute_command(self.world)
        return isOk

    def read_vdb_file(self, filepath) :
        create_vdb_command(vdb_labels.VDBFileReadLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileReadLabels.FilePathLabel, filepath)
        execute_command(self.world)
        newIds = get_result_int_vector(vdb_labels.VDBFileReadLabels.NewIdLabel)
        return newIds

    def write_vdb_file(self, filepath, particleSystemIds, volumeIds) :
        create_vdb_command(vdb_labels.VDBFileWriteLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileWriteLabels.FilePathLabel, filepath)
        set_arg_int_vector(vdb_labels.VDBFileWriteLabels.ParticleSystemIdsLabel, particleSystemIds)
        set_arg_int_vector(vdb_labels.VDBFileWriteLabels.VDBVolumeIdsLabel, volumeIds);
        execute_command(self.world)

    def create_vdb_empty_points(self, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel);
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBPointsLabel)
        execute_command(self.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId
    
    def create_vdb_points(self, positions, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBPointsLabel)
        set_arg_vector3dd_vector(vdb_labels.VDBSceneCreateLabels.PositionsLabel, positions)
        execute_command(self.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId

    def create_vdb_mesh(self, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBMeshLabel)
        execute_command(self.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId

    def create_vdb_volume(self, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBVolumeLabel)
        execute_command(self.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId

    def write_obj_file(self, vdb_mesh_id, file_path) :
        create_vdb_command(vdb_labels.VDBOBJFileWriteLabels.CommandNameLabel)
        set_arg_int(vdb_labels.VDBOBJFileWriteLabels.VDBMeshIdLabel, vdb_mesh_id)
        set_arg_string(vdb_labels.VDBOBJFileWriteLabels.FilePathLabel, file_path)
        isOk = execute_command(self.world)
        return isOk

    def read_obj_file(self, file_path) :
        create_vdb_command(vdb_labels.VDBOBJFileReadLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBOBJFileReadLabels.FilePathLabel, file_path)
        isOk = execute_command(self.world)
        if isOk == False :
            return -1
        newId = get_result_int(vdb_labels.VDBOBJFileReadLabels.VDBMeshIdLabel)
        return newId

class TestVector3df(unittest.TestCase):
    def test(self):
        v = Vector3df(1.0, 2.0, 3.0)
        self.assertEqual(1.0, v.x)
        self.assertEqual(2.0, v.y)
        self.assertEqual(3.0, v.z)

class TestVector3dfVector(unittest.TestCase):
    def test(self):
        v = []
        v.append( Vector3df(1.0, 2.0, 3.0) )
        v.append( Vector3df(4.0, 5.0, 6.0) )
        vv = Vector3dfVector()
        vv = v
        self.assertEqual(1.0, vv[0].x)
        self.assertEqual(2.0, vv[0].y)

class TestVector3dd(unittest.TestCase):
    def test(self):
        v = Vector3dd(1.0,2.0,3.0)
        self.assertEqual(1.0, v.x)
        self.assertEqual(2.0, v.y)
        self.assertEqual(3.0, v.z)

class TestVector3ddVector(unittest.TestCase):
    def test(self):
        v = []
        vv = Vector3ddVector()
        vv.add( Vector3dd(1.0, 2.0, 3.0) )
        vv.add( Vector3dd(4.0, 5.0, 6.0) )
        print(vv.values[0].x)
#        self.assertEqual(1.0, vv[0].x)
#        self.assertEqual(2.0, vv[0].y)


class PhysicsSolverCreateCommandTest(unittest.TestCase):
    def test(self):
        world = World()
        physics = PhysicsCommand(world)
        newId = physics.create_solver()
        self.assertEqual(1, newId)
#        scene = SceneCommand();
#        scene.clear(0)

class VDBCommand_test(unittest.TestCase):
    def setUp(self):
        world = World()
        self.vdb = VDBCommand(world)
        self.vdb.init()

    def test_create_vdb_points(self):
        newId = self.vdb.create_vdb_empty_points("test_vdb_points")
        self.assertEqual(1, newId)

        p = Vector3ddVector()
        p.add(Vector3dd(1.0, 2.0, 3.0))
        p.add(Vector3dd(4.0, 5.0, 6.0))
        newId = self.vdb.create_vdb_points(p, "test_vdb_points_2")
        self.assertEqual(2, newId)

    def test_create_vdb_mesh(self):
        newId = self.vdb.create_vdb_mesh("test_vdb_mesh")
        self.assertEqual(1, newId)

    def test_create_vdb_volume(self):
        newId = self.vdb.create_vdb_volume("test_vdb_volume")
        self.assertEqual(1, newId)

    def test_read_vdb_file(self):
        newIds = self.vdb.read_vdb_file("./source_river.vdb")
        print(newIds)
        self.vdb.write_vdb_file("test_write.vdb", newIds, [])
#        self.assertEqual(1, newId)

    def test_read_obj_file(self):
        newId = self.vdb.read_obj_file("./quad.obj")
        self.assertEqual(1, newId)
        self.vdb.write_obj_file(newId, "./test_write.obj")

if __name__ == '__main__':
    unittest.main()