import unittest
import CrystalPLI
from voxel_scene import *

class VoxelSceneTest(unittest.TestCase):
    def test_create_voxel(self):
        scene = Scene(World())
        voxel = VoxelScene(scene)
        resolution = [2,2,2]
        bb = Box3dd()
        voxel.create_voxel("", resolution,bb, 1)
        self.assertEqual(1, voxel.id)
        values = voxel.get_values()
        print(len(values))