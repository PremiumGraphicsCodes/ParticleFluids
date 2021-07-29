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

    def test_create_voxel(self):
        scene = Scene(World())
        command = SpaceCommand(scene)
        resolution = [2,2,2]
        bb = Box3dd()
        new_id = command.create_voxel("", resolution,bb, 1)
        self.assertEqual(1, new_id)

if __name__ == '__main__':
    unittest.main()
