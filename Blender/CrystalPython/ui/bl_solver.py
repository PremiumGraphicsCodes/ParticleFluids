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
        self.__solver = None
        self.__running = False
        self.__bl_fluids = []
        self.__bl_boundaries = []
        self.__external_force = Vector3df(0.0, 0.0, -9.8)
        self.__time_step = 0.01
        self.__export_dir_path = "tmp_txt"

    def build(self):
        if self.__solver != None :
            return

        self.__solver = SolverScene(model.scene)
        self.__solver.create()

        
    def add_fluid(self, bl_fluid) :
        self.__bl_fluids.append(bl_fluid)

    def add_boundary(self, bl_boundary) :
        self.__bl_boundaries.append(bl_boundary)

    def send(self) :
        fluids = []
        for bl_fluid in self.__bl_fluids :
            fluids.append( bl_fluid.fluid )
        self.__solver.fluids = fluids

        boundaries = []
        for bl_boundary in self.__bl_boundaries :
            boundaries.append( bl_boundary.boundary )
        self.__solver.boundaries = boundaries

        self.__solver.external_force = self.__external_force
        self.__solver.time_step = self.__time_step
        self.__solver.send()

    def start(self):

        self.__running = True

    def stop(self):
        self.__running = False

    def step(self, frame):
        self.__solver.simulate()
        for bl_fluid in self.__bl_fluids :
            bl_fluid.update()
        
        file_path = os.path.join(self.__export_dir_path, "test" + str(frame) + ".txt")
        self.__solver.export_txt(file_path)

    def is_running(self):
        return self.__running

    def reset(self):
        for bl_fluid in self.__bl_fluids :
            bl_fluid.reset()
        self.__bl_fluids.clear()
        self.__bl_boundaries.clear()
