import unittest
import CrystalPLI
from scene import *

class SceneTest(unittest.TestCase):
    def test_create_particle_system_scene(self):
        scene = Scene(World())
        positions = Vector3ddVector()
        positions.add(Vector3dd(1.0, 2.0, 3.0))
        positions.add(Vector3dd(4.0, 5.0, 6.0))
        color = ColorRGBAf()
        new_id = scene.create_particle_system_scene(positions, "", 1.0, color, 1)
        self.assertEqual(1, new_id)
        scene.delete(new_id, False)
#        self.fail("Not implemented")

#if __name__ == '__main__':
#    unittest.main()
