import bpy
import os

from physics.solver_scene import SolverScene
from ui.bl_fluid import BLFluid
from ui.bl_boundary import BLBoundary
from ui.bl_triangle_mesh import BLTriangleMesh
from scene.triangle_mesh_scene import TriangleMeshScene
from CrystalPLI import Vector3df
from scene.file_io import FileIO
import threading

class BLSolver :
    def __init__(self) :
        self.__solver = None
        self.__running = False
        self.__bl_fluids = []
        self.__bl_boundaries = []
        self.__external_force = Vector3df(0.0, 0.0, -9.8)
        self.__time_step = 0.01
        self.__export_dir_path = "tmp_txt"
        self.__bl_mesh = None
        self.__iteration = 1
        self.__tmp_meshes = []

    def build(self, scene):
        if self.__solver != None :
            return

        self.__solver = SolverScene(scene)
        self.__solver.create()
        
    def add_fluid(self, bl_fluid) :
        self.__bl_fluids.append(bl_fluid)

    def add_boundary(self, bl_boundary) :
        self.__bl_boundaries.append(bl_boundary)

    def set_export_path(self, dir_path) :
        self.__export_dir_path = dir_path

    def set_effect_length(self, effect_radius) :
        self.__solver.effect_length = effect_radius

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
        thread = threading.Thread(target=self.run)
        thread.start()

    def stop(self):
        self.__running = False

    def set_start_frame(self, frame) :
        self.start_frame = frame

    def set_end_frame(self, frame):
        self.end_frame = frame

    def set_iteration(self, iter) :
        self.__iteration = iter

    def run(self) :
        #win = bpy.context.window_manager
        #win.progress_begin(self.start_frame, self.end_frame)
        for i in range(self.start_frame, self.end_frame) :
            self.step(i)
        #    bpy.context.scene.frame_current = i
            bpy.context.scene.solver_property.progress_prop = i
        #    win.progress_update(i)
        #win.progress_end()

    def step(self, frame):
        for i in range(0, self.__iteration) :
            self.__solver.simulate()

        for fluid in self.__bl_fluids :
            fluid.send_shader()
        
        macro_file_path = os.path.join(self.__export_dir_path, "macro" + str(frame) + ".ply")
        self.__solver.export_pcd(macro_file_path, True)

        #for o in self.__tmp_meshes :
        #    bpy.data.objects.remove(o)     
        #bpy.ops.import_mesh.ply(filepath=macro_file_path)
        #self.__tmp_meshes = bpy.context.selected_objects

    def is_running(self):
        return self.__running

    def reset(self):
#        for bl_fluid in self.__bl_fluids :
#            bl_fluid.reset()
        self.__bl_fluids.clear()
        self.__bl_boundaries.clear()

    def render(self):
        for bl_fluid in self.__bl_fluids :
            bl_fluid.render()
        for bl_boundary in self.__bl_boundaries :
            bl_boundary.draw()
