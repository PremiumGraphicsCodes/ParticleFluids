import unittest
from scene.particle_system_scene import *
from physics.fluid_scene import *
from physics.solver_scene import *
from physics.csg_boundary_scene import CSGBoundaryScene
from CrystalPLI import Vector3df

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

        boundaries = []
        boundary = CSGBoundaryScene(scene)
        boundary.create()
        boundary.send()
        boundaries.append(boundary)

        solver.fluids = fluids
        solver.boundaries = boundaries
        solver.external_force = Vector3df(0.0, 0.0, -9.8)
        solver.send()
        solver.simulate()

        solver.export_pcd("export_macro.pcd", False)
        solver.export_pcd("export_micro.pcd", True)
