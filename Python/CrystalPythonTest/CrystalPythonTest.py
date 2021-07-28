
import CrystalPython
import unittest
import os
import scene_labels
import space_labels
import physics_labels
import vdb_command

from vdb_command import VDBCommand
from CrystalPython import *

print('doc=', CrystalPython.__doc__)

class Scene :
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

class SpaceCommand :
    def __init__(self, world):
        self.world = world

    def create_sparse_volume(resolution, boundingBox, layer, name) :
        create_sparse_command(space_labels.SparseVolumeSceneCreateLabels.CommandNameLabel);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionXLabel, resolution[0]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionYLabel, resolution[1]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionZLabel, resolution[2]);
        set_arg_box3df(space_labels.SparseVolumeSceneCreateLabels.BoundingBoxLabel, boundingBox);
        set_arg_string(space_labels.SparseVolumeSceneCreateLabels.NameLabel, name);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.LayerLabel, layer);
        execute_command(self.world)
        newId = get_result_int(space_labels.SparseVolumeSceneCreateLabels.NewIdLabel);
        return newId


class PhysicsCommand :
    def __init__(self, world) :
        self.world = world

    def create_solver(self) :
        create_physics_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command(self.world)
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
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
#        print(vv.values[0].x)
#        self.assertEqual(1.0, vv[0].x)
#        self.assertEqual(2.0, vv[0].y)

def calc_distance_squared(lhs, rhs) :
    dx = lhs.x - rhs.x
    dy = lhs.y - rhs.y
    dz = lhs.z - rhs.z
    return dx * dx + dy * dy + dz * dz

#def are_same(lhs, rhs, tolerance) :

class TestBox3df(unittest.TestCase):
    def test(self):
        box = Box3df(Vector3df(0,0,0), Vector3df(1,1,1))
        dist = calc_distance_squared(Vector3df(0,0,0), Vector3df(1,1,1))
        print(dist)
#        self.assertEqual(Vector3df(0,0,0), box.min)

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
        scene = Scene(world)
        self.vdb = VDBCommand(scene)
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
        self.assertEqual([1], newIds)
#        print(newIds)
        self.vdb.write_vdb_file("test_write.vdb", newIds, [])
#        self.assertEqual(1, newId)

    def test_read_obj_file(self):
        newId = self.vdb.read_obj_file("./quad.obj")
        self.assertEqual(1, newId)
        self.vdb.write_obj_file(newId, "./test_write.obj")

    def test_convert_ps_to_volume(self):
        ps_id = self.vdb.create_vdb_empty_points("")
        volume_id = self.vdb.create_vdb_volume("")
        self.vdb.convert_ps_to_volume(ps_id, volume_id, 1.0)

if __name__ == '__main__':
    unittest.main()