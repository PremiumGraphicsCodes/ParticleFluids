import unittest
import CrystalPLI
from particle_system_scene import *
from wire_frame_scene import *
from scene import *

class ParticleSystemSceneTest(unittest.TestCase):
#    def test_create_mesh_scene(self):
#        scene = Scene(World())

    def test_create_particle_system_scene(self):
        scene = Scene(World())
        particle_system = self.__create_test_particle_system(scene)
        self.assertEqual(1, particle_system.id)

    def test_write_pcd(self):
        scene = Scene(World())
        particle_system = self.__create_test_particle_system(scene)
        particle_system.export_pcd_file("test.pcd")

    def test_import_pcd(self):
        scene = Scene(World())
        particle_system = ParticleSystemScene(scene)
        particle_system.import_pcd_file("test.pcd")
        self.assertEqual(1, particle_system.id)

    def test_get_positions(self):
        scene = Scene(World())
        particle_system = self.__create_test_particle_system(scene)
        positions = particle_system.get_positions()
        print(positions.values[0].x)
        print(positions.values[0].y)
        
    def __create_test_particle_system(self, scene) :
        positions = Vector3ddVector()
        positions.add(Vector3dd(1.0, 2.0, 3.0))
        positions.add(Vector3dd(4.0, 5.0, 6.0))
        color = ColorRGBAf()
        particle_system = ParticleSystemScene(scene)
        particle_system.create(positions, "", 1.0, color, 1)
        return particle_system

#if __name__ == '__main__':
#    unittest.main()
