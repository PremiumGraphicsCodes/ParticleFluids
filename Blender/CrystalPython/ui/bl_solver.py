import bpy
import os

from ui.model import Model as model
from physics.solver_scene import SolverScene
from ui.bl_fluid import BLFluid
from ui.bl_boundary import BLBoundary
from CrystalPLI import Vector3df
from scene.file_io import FileIO

class BLSolver :
    def __init__(self) :
        self.solver = None
        self.__running = False
        self.fluid = BLFluid(model.scene)
        self.boundary = BLBoundary(model.scene)
        self.time_step = 0
        self.external_force = Vector3df(0.0, 0.0, -9.8)
        self.time_step = 0.01

    def build(self):
        if self.solver != None :
            return

        self.fluid.build()
        self.fluid.convert_to_polygon_mesh("BLFluid")

        self.boundary.build()
        self.boundary.convert_to_polygon_mesh("BLBoundary")

        self.solver = SolverScene(model.scene)
        self.solver.create()
        
        fluids = []
        fluids.append(self.fluid.fluid)
        self.solver.fluids = fluids

        boundaries = []
        boundaries.append(self.boundary.boundary)
        self.solver.boundaries = boundaries

        #external_force = bpy.context.scene.solver_property.external_force_prop
        #self.solver.external_force = Vector3df(external_force[0],external_force[1],external_force[2])

        #self.solver.time_step = bpy.context.scene.solver_property.time_step_prop

        self.solver.send()
        self.solver.simulate()

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self):
        self.solver.simulate()
        self.fluid.update()
        
        file_path = os.path.join("tmp_txt", "test" + str(self.time_step) + ".txt")
        FileIO.export_txt(model.scene, self.fluid.fluid.id, file_path)
        self.time_step += 1

    def is_running(self):
        return self.__running
