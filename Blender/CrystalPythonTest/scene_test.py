import unittest
import CrystalPLI
from scene import *

class SceneTest(unittest.TestCase):
    def test_create_mesh_scene(self):
        scene = Scene(World())

    def __create_test_particle_system(self) :
        scene = Scene(World())
        positions = Vector3ddVector()
        positions.add(Vector3dd(1.0, 2.0, 3.0))
        positions.add(Vector3dd(4.0, 5.0, 6.0))
        color = ColorRGBAf()
        new_id = scene.create_particle_system_scene(positions, "", 1.0, color, 1)
        return new_id

    def test_create_particle_system_scene(self):
        new_id = self.__create_test_particle_system()
        self.assertEqual(1, new_id)

    def test_create_wire_frame_scene(self):
        scene = Scene(World())
        color = ColorRGBAf()
        new_id = scene.create_empty_wire_frame_scene("", 1.0,color,1)
        self.assertEqual(1, new_id)

#if __name__ == '__main__':
#    unittest.main()
