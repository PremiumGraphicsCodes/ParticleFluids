import unittest
from physics.emitter_scene import EmitterScene

class EmitterSceneTest(unittest.TestCase):
    def test_create(self):
        world = World()
        scene = Scene(world)
        fluid = EmitterScene(scene)
        fluid.create()
        fluid.send()
        #p = fluid.get_positions()
        
