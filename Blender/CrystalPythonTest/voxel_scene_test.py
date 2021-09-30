import unittest
import CrystalPLI
from triangle_mesh_scene import *
from voxel_scene import *

class VoxelSceneTest(unittest.TestCase):
    def test_create_voxel(self):
        scene = Scene(World())
        voxel = VoxelScene(scene)
        resolution = [2,2,2]
        bb = Box3dd()
        voxel.create_voxel("", resolution,bb)
        self.assertEqual(1, voxel.id)
        values = voxel.get_values()
        print(len(values))

    def test_voxelizer(self):
        scene = Scene(World())
        mesh = TriangleMeshScene(scene)
        mesh.create(Triangle3ddVector(), "")
        voxel = VoxelScene(scene)
        voxel.create_empty_voxel("")
        voxelizer = Voxelizer(scene)
        voxelizer.voxelize(mesh.id, voxel.id, 1.0)
