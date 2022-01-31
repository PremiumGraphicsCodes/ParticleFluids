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
from bpy_extras.io_utils import ImportHelper

world = World()
scene = Scene(world)


class ParticleSystemSequenceMeshingOperator(bpy.types.Operator, ImportHelper) :
    bl_idname = "pg.particlesystemsequencemeshingoperator"
    bl_label = "ParticleSystem"
#    bl_description = "Hello"
    filter_glob : bpy.props.StringProperty(
            default="*.ply",
            options={'HIDDEN'}
            )

    files : bpy.props.CollectionProperty(
        name="PLY files",
        type=bpy.types.OperatorFileListElement,
        )

    directory : bpy.props.StringProperty(subtype='DIR_PATH')
 
    def execute(self, context) :
        for file in self.files :
            print(file.name)
            self.convert(file.name)

        return {'FINISHED'}

    def convert(self, file_name) :
        prop = bpy.context.scene.meshing_property

        ps_file_path = os.path.join(self.directory, file_name)
        basename_without_ext = os.path.splitext(os.path.basename(file_name))[0]
        export_file_path = os.path.join(self.directory, basename_without_ext + ".vdb") #basename_without_ext + ".stl")

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
        #params.append("-sw")
        #params.append(str(prop.smoothing_width_prop))
        #params.append("-si")
        #params.append(str(prop.smoothing_iter_prop))
            
        result = subprocess.run(params, shell=True)
        #if result != -1 :
            #for o in self.tmp_volumes :
            #    bpy.data.objects.remove(o)                

            #bpy.ops.object.volume_import(filepath=export_file_path, align='WORLD', location=(0, 0, 0), scale=(1, 1, 1))
            #self.tmp_volumes = bpy.context.selected_objects


class MeshingProperty(bpy.types.PropertyGroup) :
    input_path_prop : bpy.props.StringProperty(
        name="input_path",
        description="Path to Directory",
        default="tmp_txt",
        maxlen=1024,
        subtype='DIR_PATH'
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
        
class ParticleSystemSequenceMeshingPanel(bpy.types.Panel):
    bl_label = "PSSeqMeshing"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "VDBTools"
    bl_context = "objectmode"

    def draw(self, context):
        prop = context.scene.meshing_property
        self.layout.prop(prop, "input_path_prop", text="InputPath")
        self.layout.prop(prop, "output_path_prop", text="OutputPath")
        self.layout.prop(prop, "particle_radius_prop", text="ParticleRadius")
        self.layout.prop(prop, "cell_length_prop", text="CellLength")
        self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname, text="Start", icon = "PLAY")

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

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.meshing_property
#        bpy.app.handlers.frame_change_pre.remove(my_handler)