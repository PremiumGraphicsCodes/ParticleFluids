import bpy
import os

from physics.solver_scene import SolverScene
from ui.bl_fluid import BLFluid
from ui.bl_boundary import BLBoundary
from ui.bl_triangle_mesh import BLTriangleMesh
from scene.triangle_mesh_scene import TriangleMeshScene
from CrystalPLI import Vector3df
from scene.file_io import FileIO
import subprocess

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

    def set_start_frame(self, frame) :
        self.start_frame = frame

    def set_end_frame(self, frame):
        self.end_frame = frame

    def set_iteration(self, iter) :
        self.__iteration = iter

    def set_vdb_particle_radius(self, radius) :
        self.__vdb_particle_radius = radius

    def set_vdb_cell_length(self, length) :
        self.__vdb_cell_length = length

    def step(self, frame):
        for i in range(0, self.__iteration) :
            self.__solver.simulate()
        
        macro_file_path = os.path.join(self.__export_dir_path, "macro" + str(frame) + ".pcd")
        self.__solver.export_pcd(macro_file_path, False)

    def export_vdb(self, frame) :
        #prop = bpy.context.scene.meshing_property

        ps_file_path = os.path.join(self.__export_dir_path, "macro" + str(frame) + ".pcd")
        export_file_path = os.path.join(self.__export_dir_path, "volume" + str(frame) + ".vdb") #basename_without_ext + ".stl")

        params = []
        params.append('VDBTool')
        params.append("-i")
        params.append(str(ps_file_path))
        params.append("-o")
        params.append(str(export_file_path))
        params.append("-r")
        params.append(str(self.__vdb_particle_radius))
        params.append("-v")
        params.append(str(self.__vdb_cell_length))
        #params.append("-t")
        #params.append(str(prop.threshold_prop))
        #params.append("-a")
        #params.append(str(prop.mesh_adaptivity_prop))
        #params.append("-sw")
        #params.append(str(prop.smoothing_width_prop))
        #params.append("-si")
        #params.append(str(prop.smoothing_iter_prop))
            
        result = subprocess.run(params, shell=True)
        if result != -1 :
            for o in self.tmp_volumes :
                bpy.data.objects.remove(o)                

            bpy.ops.object.volume_import(filepath=export_file_path, align='WORLD', location=(0, 0, 0), scale=(1, 1, 1))
            self.tmp_volumes = bpy.context.selected_objects


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
