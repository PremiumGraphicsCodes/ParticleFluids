import unittest
import CrystalPLI
from polygon_mesh_scene import *

class PolygonMeshSceneTest(unittest.TestCase) :
    def test_create_polygon_mesh_scene(self):
        scene = Scene(World())
        mesh = PolygonMeshScene(scene)
        mesh.create_empty_polygon_mesh_scene("",1)
        self.assertEqual(1, mesh.id)

    #def test_add_face():
    #    scene = Scene(World())
    #    mesh = PolygonMeshScene(scene)
    #    mesh.add_face([0,1,2])

    def test_import_obj(self):
        scene = Scene(World())
        mesh = PolygonMeshScene(scene)
        mesh.import_obj_file("test_read.obj")