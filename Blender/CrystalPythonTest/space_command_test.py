import unittest
import CrystalPLI
from space_command import *

class SpaceCommandTest(unittest.TestCase):
    def test_create_sparse_volume(self):
        scene = Scene(World())
        command = SpaceCommand(scene)
        resolution = [2,2,2]
        bb = Box3dd()
        new_id = command.create_sparse_volume(resolution, bb, 1, "")
        self.assertEqual(1, new_id)

#    def test_voxelize(self):
#        scene = Scene(World())
#        positions = Vector3ddVector()
#        color = ColorRGBAf()
#        ps_id = scene.create_particle_system_scene(positions, "", 1.0, color, 1)
#        self.assertEqual(1, ps_id)


if __name__ == '__main__':
    unittest.main()
