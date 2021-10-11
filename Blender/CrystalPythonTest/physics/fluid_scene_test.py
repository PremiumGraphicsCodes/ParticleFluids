import unittest
from physics.fluid_scene import *

class FluidSceneTest(unittest.TestCase):
    def test_create(self):
        world = World()
        scene = Scene(world)
        fluid = FluidScene(scene)
        fluid.create()
        fluid.send()

