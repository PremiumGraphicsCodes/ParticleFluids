
import CrystalPLI
import unittest
#import os
#import vdb_command_test

from CrystalPLI import *

from scene_test import *
from space_command_test import *
from wire_frame_scene_test import *
from polygon_mesh_scene_test import *
#from vdb_command_test import *
from physics_command_test import *

#print('doc=', CrystalPLI.__doc__)

class TestVector2df(unittest.TestCase):
    def test(self):
        v = Vector2df(1.0, 2.0)
        self.assertEqual(1.0, v.x)
        self.assertEqual(2.0, v.y)

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
        self.assertEqual(3.0, vv[0].z)

class TestColorRGBAf(unittest.TestCase):
    def test(self):
        v = ColorRGBAf(0.1, 0.2, 0.3, 0.4)
        self.assertAlmostEqual(0.1, v.r)
        self.assertAlmostEqual(0.2, v.g)
        self.assertAlmostEqual(0.3, v.b)
        self.assertAlmostEqual(0.4, v.a)

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

#class TestBox3df(unittest.TestCase):
#    def test(self):
#        box = Box3df(Vector3df(0,0,0), Vector3df(1,1,1))
#        dist = calc_distance_squared(Vector3df(0,0,0), Vector3df(1,1,1))
#        print(dist)
#        self.assertEqual(Vector3df(0,0,0), box.min)


class TestRunner(unittest.TestCase): 
    def test_runner(self):
        test_suite = unittest.TestSuite()
        test_suite.addTest(unittest.makeSuite(ParticleSystemSceneTest))
        test_suite.addTest(unittest.makeSuite(WireFrameSceneTest))
        test_suite.addTest(unittest.makeSuite(PolygonMeshSceneTest))
        test_suite.addTest(unittest.makeSuite(SpaceCommandTest))
        test_suite.addTest(unittest.makeSuite(SolverSceneTest))
        test_suite.addTest(unittest.makeSuite(CSGBoundarySceneTest))
        test_suite.addTest(unittest.makeSuite(FluidSceneTest))

#        tests = unittest.defaultTestLoader.discover("CrystalPythonTest", pattern="*.py")
#        print(tests)
#        test_suite.addTest(tests)

        unittest.TextTestRunner().run(test_suite)

if __name__ == '__main__':
    unittest.main()