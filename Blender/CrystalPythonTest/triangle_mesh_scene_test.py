import unittest
import CrystalPLI
from triangle_mesh_scene import *

class TriangleMeshSceneTest(unittest.TestCase) :
    def test_create_triangle_mesh_scene(self):
        scene = Scene(World())
        mesh = TriangleMeshScene(scene)
