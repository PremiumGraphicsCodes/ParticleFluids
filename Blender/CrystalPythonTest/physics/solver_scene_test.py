import unittest
from physics.fluid_scene import *
from physics.solver_scene import *

class SolverSceneTest(unittest.TestCase):
    def test(self):
        world = World()
        scene = Scene(world)
        solver = SolverScene(scene)
        solver.create()
        self.assertEqual(1, solver.id)

        fluids = []
        fluid = FluidScene(scene)
        fluid.create()
        fluids.append(fluid)

        solver.send(fluids)
        solver.simulate()
