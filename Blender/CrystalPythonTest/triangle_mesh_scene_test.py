import unittest
import CrystalPLI
from triangle_mesh_scene import *

class TriangleMeshSceneTest(unittest.TestCase) :
    def test_create_triangle_mesh_scene(self):
        scene = Scene(World())
        mesh = TriangleMeshScene(scene)

        v0 = Vector3dd(0.0, 0.0, 0.0)
        v1 = Vector3dd(1.0, 0.0, 0.0)
        v2 = Vector3dd(1.0, 1.0, 0.0)
        triangles = Triangle3ddVector()
        triangles.add(Triangle3dd(v0, v1, v2))
        mesh.create(triangles, "test", 0)
        self.assertEqual(1, mesh.id)