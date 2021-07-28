import unittest
from physics_command import *

class PhysicsSolverCreateCommandTest(unittest.TestCase):
    def test(self):
        world = World()
        physics = PhysicsCommand(world)
        newId = physics.create_solver()
        self.assertEqual(1, newId)
#        scene = SceneCommand();
#        scene.clear(0)


if __name__ == '__main__':
    unittest.main()
