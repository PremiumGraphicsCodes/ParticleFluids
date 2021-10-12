import unittest
from scene.particle_system_scene import *
from physics.fluid_scene import *
from physics.solver_scene import *

class SolverSceneTest(unittest.TestCase):
    def test(self):
        world = World()
        scene = Scene(world)
        solver = SolverScene(scene)
        solver.create()
        self.assertEqual(1, solver.id)

        ps = ParticleSystemScene(scene)
        ps.create_empty("")

        fluids = []
        fluid = FluidScene(scene)
        fluid.create()
        fluid.source_particle_system_id = ps.id
        fluid.send()
        fluids.append(fluid)

        solver.send(fluids)
        solver.simulate()
