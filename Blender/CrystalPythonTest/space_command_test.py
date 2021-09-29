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

#class VoxelizerTest(unittest.TestCase):
#    def test_voxelize(self):
#        scene = Scene(World())
#        voxel = VoxelScene(scene)
#        voxelizer = Voxelizer(scene)
#        voxelizer.voxelize(mesh_id, voxel_id, divide_length)

if __name__ == '__main__':
    unittest.main()
