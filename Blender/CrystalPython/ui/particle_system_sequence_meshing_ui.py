import bpy
from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from physics.surface_builder import SurfaceBuilder
from CrystalPLI import Vector3dd, Vector3ddVector
from scene.particle_system_scene import ParticleSystemScene
from scene.triangle_mesh_scene import TriangleMeshScene
from scene.file_io import FileIO
from scene.scene import *
from bpy.app.handlers import persistent
import os
import glob
import subprocess

from CrystalPLI import World
from scene.scene import Scene


world = World()
scene = Scene(world)


class MeshingRunner :
    def __init__(self) :
        self.__is_running = False
        self.__bl_mesh = None

    def start(self) :
        global scene
        self.__is_running = True
        if self.__bl_mesh == None :
            self.__bl_mesh = BLTriangleMesh(scene)
            self.__bl_mesh.mesh.create_empty("")
            self.__bl_mesh.convert_to_polygon_mesh("")               

    def stop(self) :
        self.__is_running = False

    def step(self, frame) :
        prop = bpy.context.scene.meshing_property

        ps_file_path = os.path.join(prop.input_path_prop, "macro" + str(frame) + ".pcd")
        export_file_path = os.path.join(prop.output_path_prop, "volume" + str(frame) + ".vdb") #basename_without_ext + ".stl")

        params = []
        params.append('VDBTool')
        params.append("-i")
        params.append(str(ps_file_path))
        params.append("-o")
        params.append(str(export_file_path))
        params.append("-r")
        params.append(str(prop.particle_radius_prop))
        params.append("-v")
        params.append(str(prop.cell_length_prop))
        #params.append("-t")
        #params.append(str(prop.threshold_prop))
        #params.append("-a")
        #params.append(str(prop.mesh_adaptivity_prop))
        params.append("-sw")
        params.append(str(prop.smoothing_width_prop))
        params.append("-si")
        params.append(str(prop.smoothing_iter_prop))
            
        result = subprocess.run(params, shell=True)
#        if result != -1 :
#            self.__bl_mesh.mesh.import_stl(export_file_path)
#            self.__bl_mesh.update()
            
    def is_running(self) :
        return self.__is_running

runner = MeshingRunner()

@persistent
def my_handler(scene):
    if runner.is_running() :
        runner.step(scene.frame_current)

class ParticleSystemSequenceMeshingOperator(bpy.types.Operator) :
    bl_idname = "pg.particlesystemsequencemeshingoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"
    
    def execute(self, context) :
        if not runner.is_running() :
            runner.start()
        else :
            runner.stop()
        return {'FINISHED'}


class MeshingProperty(bpy.types.PropertyGroup) :
    input_path_prop : bpy.props.StringProperty(
        name="input_path",
        description="Path to Directory",
        default="tmp_txt",
        maxlen=1024,
        subtype='DIR_PATH'
        )

    do_export_stl_prop : bpy.props.BoolProperty(
        name="Export",
        description="Export",
        default=False
    )

    output_path_prop : bpy.props.StringProperty(
        name="output_path",
        description="Path to Directory",
        default="tmp_stl",
        maxlen=1024,
        subtype='DIR_PATH'
    )
        
    particle_radius_prop : bpy.props.FloatProperty(
        name="particle_radius",
        description="ParticleRadius",
        default=1.0,
        min = 0.0,
        max = 100.0,
        )

    cell_length_prop : bpy.props.FloatProperty(
        name="cell_length",
        description="CellLength",
        default=0.5,
        min = 0.0,
        max = 100.0,
    )

    threshold_prop : bpy.props.FloatProperty(
        name="threshold",
        description="Threshold",
        default=0.0,
        min = 0.0,
        )

    mesh_adaptivity_prop : bpy.props.FloatProperty(
        name="mesh_adaptivity",
        description = "Adaptivity",
        default = 1.0,
        min = 0.0,
    )

    smoothing_width_prop : bpy.props.IntProperty(
        name="smoothing_width",
        description = "SmoothingWidth",
        default = 1,
        min = 0,
    )

    smoothing_iter_prop : bpy.props.IntProperty(
        name="smoothing_iter",
        description = "SmoothingIiter",
        default = 1,
        min = 0,
    )
        
class ParticleSystemSequenceMeshingPanel(bpy.types.Panel):
    bl_label = "PSSeqMeshing"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "PFTools"
    bl_context = "objectmode"

    def draw(self, context):
        prop = context.scene.meshing_property
        self.layout.prop(prop, "input_path_prop", text="InputPath")
        self.layout.prop(prop, "do_export_stl_prop", text="Export")
        self.layout.prop(prop, "output_path_prop", text="OutputPath")
        self.layout.prop(prop, "particle_radius_prop", text="ParticleRadius")
        self.layout.prop(prop, "cell_length_prop", text="CellLength")
#        self.layout.prop(prop, "threshold_prop", text="Threshold")
#        self.layout.prop(prop, "mesh_adaptivity_prop", text="Adaptivity")
        self.layout.prop(prop, "smoothing_width_prop", text="SmoothingWidth")
        self.layout.prop(prop, "smoothing_iter_prop", text="SmoothingIter")
        if not runner.is_running() :
            self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname, text="Start", icon = "PLAY")
        else :
            self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname, text="Stop", icon='PAUSE')

classes = [
    ParticleSystemSequenceMeshingOperator,
    ParticleSystemSequenceMeshingPanel,
    MeshingProperty
]

class ParticleSystemSequenceMeshingUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.meshing_property = bpy.props.PointerProperty(type=MeshingProperty)
        bpy.app.handlers.frame_change_pre.append(my_handler)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.meshing_property
#        bpy.app.handlers.frame_change_pre.remove(my_handler)