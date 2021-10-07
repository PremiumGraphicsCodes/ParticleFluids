import unittest
from physics.solver_scene import *

class SolverSceneTest(unittest.TestCase):
    def test(self):
        world = World()
        scene = Scene(world)
        physics = SolverScene(scene)
        newId = physics.create()
        self.assertEqual(1, newId)

