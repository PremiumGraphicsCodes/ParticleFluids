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
        self.__bl_fluids = []
        self.__bl_boundaries = []
        self.__frame = 1
        self.external_force = Vector3df(0.0, 0.0, -9.8)
        self.time_step = 0.01
        self.export_dir_path = "tmp_txt"

    def build(self):
        if self.solver != None :
            return

        self.solver = SolverScene(model.scene)
        self.solver.create()
        
        #external_force = bpy.context.scene.solver_property.external_force_prop
        #self.solver.external_force = Vector3df(external_force[0],external_force[1],external_force[2])

        #self.solver.time_step = bpy.context.scene.solver_property.time_step_prop

    def add_fluid(self, bl_fluid) :
        self.__bl_fluids.append(bl_fluid)

    def add_boundary(self, bl_boundary) :
        self.__bl_boundaries.append(bl_boundary)

    def send(self) :
        fluids = []
        for bl_fluid in self.__bl_fluids :
            fluids.append( bl_fluid.fluid )
        self.solver.fluids = fluids

        boundaries = []
        for bl_boundary in self.__bl_boundaries :
            boundaries.append( bl_boundary.boundary )
        self.solver.boundaries = boundaries

        self.solver.send()

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self, frame):
        if frame == self.__frame :
            return
        self.solver.simulate()
        for bl_fluid in self.__bl_fluids :
            bl_fluid.update()
        
        file_path = os.path.join(self.export_dir_path, "test" + str(frame) + ".txt")
        self.solver.export_txt(file_path)
        self.__frame = frame

    def is_running(self):
        return self.__running

    def reset(self):
        for bl_fluid in self.__bl_fluids :
            bl_fluid.reset()
        self.__bl_fluids.clear()
        self.__bl_boundaries.clear()
        self.__frame = 1

