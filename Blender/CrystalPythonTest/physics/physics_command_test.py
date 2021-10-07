import unittest
from physics.solver_scene import *
from physics.fluid_scene import *
from physics.csg_boundary_scene import *

class SolverSceneTest(unittest.TestCase):
    def test(self):
        world = World()
        scene = Scene(world)
        physics = SolverScene(scene)
        newId = physics.create()
        self.assertEqual(1, newId)

class FluidSceneTest(unittest.TestCase):
    def test_create(self):
        world = World()
        scene = Scene(world)
        fluid = FluidScene(scene)
        fluid.create()
        fluid.send()

class CSGBoundarySceneTest(unittest.TestCase):
    def test_create(self):
        world = World()
        scene = Scene(world)
        boundary = CSGBoundaryScene(scene)
        boundary.create()
        boundary.send()
        boundary.delete()

if __name__ == '__main__':
    unittest.main()
