import unittest
from scene.particle_system_scene import *
from scene.triangle_mesh_scene import *
from physics.surface_builder import *

class SurfaceBuilderTest(unittest.TestCase):
    def test_build(self):
        scene = Scene(World())

        particle_system = ParticleSystemScene(scene)
        particle_system.create_empty("")

        triangle_mesh = TriangleMeshScene(scene)
        triangle_mesh.create_empty("")

        builder = SurfaceBuilder(scene)
        builder.build_anisotorpic(particle_system.id, triangle_mesh.id, 1.0, 2.0)

if __name__ == '__main__':
    unittest.main()
