
import CrystalPython
import unittest
import os
import scene_labels
import space_labels
import physics_labels
import vdb_command
import vdb_command_test

from vdb_command import *
from CrystalPython import *

from vdb_command_test import VDBCommand_test

print('doc=', CrystalPython.__doc__)

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

class TestRunner(unittest.TestCase): 
    def test_runner(self):
        test_suite = unittest.TestSuite()
        test_suite.addTest(unittest.makeSuite(VDBCommand_test))
#        test_suite.addTest(unittest.makeSuite(test.test_mod2.TestMod2))
        unittest.TextTestRunner().run(test_suite)

if __name__ == '__main__':
    unittest.main()