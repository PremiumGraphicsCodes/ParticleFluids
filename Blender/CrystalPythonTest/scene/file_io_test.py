import unittest
import CrystalPLI
from scene.particle_system_scene import ParticleSystemScene
#from scene.wire_frame_scene import *
from scene.scene import Scene

class FileIOTest(unittest.TestCase):
    def test_export_txt(self):
        pass

    def __create_test_particle_system(self, scene) :
        positions = Vector3ddVector()
        positions.add(Vector3dd(1.0, 2.0, 3.0))
        positions.add(Vector3dd(4.0, 5.0, 6.0))
        color = ColorRGBAf()
        particle_system = ParticleSystemScene(scene)
        particle_system.create(positions, "", 1.0, color, 1)
        return particle_system
