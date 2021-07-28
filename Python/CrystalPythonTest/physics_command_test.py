import unittest
from physics_command import *

class PhysicsSolverCreateCommandTest(unittest.TestCase):
    def test(self):
        world = World()
        scene = Scene(world)
        physics = PhysicsCommand(scene)
        newId = physics.create_solver()
        self.assertEqual(1, newId)

class FluidSceneTest(unittest.TestCase):
    def test_create(self):
        world = World()
        scene = Scene(world)
        fluid = FluidScene(scene)
        fluid.create()
        fluid.send()

if __name__ == '__main__':
    unittest.main()
