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
import threading

from CrystalPLI import World
from scene.scene import Scene
from bpy_extras.io_utils import ImportHelper

world = World()
scene = Scene(world)

class VDBConverter :
    def __init__(self) :
        self.__files = []
        self.__running = False
        self.__directory = ""
        self.__current_index = 0

    def is_running(self) :
        return self.__running

    def set_dir(self, dir) :
        self.__directory = dir

    def set_files(self, files) :
        self.__files = files

    def run(self):
        count = len(self.__files)
        start = self.__current_index
        for i in range(start, count) :
            if self.__running :
                file = self.__files[i]
                self.convert(file)
                self.__current_index = i

    def start(self):
        self.__current_index = 0
        self.__running = True
        thread = threading.Thread(target=self.run)
        thread.start()

    def pause(self):
        self.__running = False

    def stop(self):
        self.__running = False
        self.__current_index = 0

    def resume(self):
        thread = threading.Thread(target=self.run)
        thread.start()
        self.__running = True

    def convert(self, file_name) :
        prop = bpy.context.scene.meshing_property
        print("converting " + file_name)

        ps_file_path = os.path.join(self.__directory, file_name)
        basename_without_ext = os.path.splitext(os.path.basename(file_name))[0]
        export_file_path = os.path.join(self.__directory, basename_without_ext + ".vdb") #basename_without_ext + ".stl")
        
        addon_dirpath = os.path.dirname(__file__)
        tool_path = os.path.join(addon_dirpath, '../vdb/VDBTool')

        params = []
        params.append(tool_path)
        params.append("-i")
        params.append(str(ps_file_path))
        params.append("-o")
        params.append(str(export_file_path))
        params.append("-r")
        params.append(str(prop.particle_radius_prop))
        params.append("-v")
        params.append(str(prop.cell_length_prop))
            
        result = subprocess.run(params, shell=True)
        #if result != -1 :
            #for o in self.tmp_volumes :
            #    bpy.data.objects.remove(o)                

            #bpy.ops.object.volume_import(filepath=export_file_path, align='WORLD', location=(0, 0, 0), scale=(1, 1, 1))
            #self.tmp_volumes = bpy.context.selected_objects


runner = VDBConverter()

class PARTICLE_FLUIDS_PSToVolumeStartOperator(bpy.types.Operator, ImportHelper) :
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
        global runner
        filenames = []
        for f in self.files :
            filenames.append(f.name)
        runner.set_dir(self.directory)
        runner.set_files(filenames)
        runner.start()
        return {'FINISHED'}

class PARTICLE_FLUIDS_PSToVolumePauseOperator(bpy.types.Operator) :
    bl_idname = "pg.particlesystemsequencemeshingpauseoperator"
    bl_label = "ParticleSystem"

    def execute(self, context) :
        global runner
        runner.pause()
        return {'FINISHED'}

class PARTICLE_FLUIDS_PSToVolumeResumeOperator(bpy.types.Operator) :
    bl_idname = "pg.particlesystemsequencemeshingresumeoperator"
    bl_label = "ParticleSystem"

    def execute(self, context) :
        global runner
        runner.resume()
        return {'FINISHED'}

class ParticleSystemSequenceMeshingCancelOperator(bpy.types.Operator) :
    bl_idname = "pg.particlesystemsequencemeshingcanceloperator"
    bl_label = "ParticleSystem"

    def execute(self, context) :
        global runner
        runner.stop()
        return {'FINISHED'}

class PARTICLE_FLUIDS_PSToVolumeProperty(bpy.types.PropertyGroup) :        
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
        self.layout.prop(prop, "particle_radius_prop", text="ParticleRadius")
        self.layout.prop(prop, "cell_length_prop", text="CellLength")

        self.layout.separator()
        row = self.layout.row(align=False)
        row.operator(PARTICLE_FLUIDS_PSToVolumeStartOperator.bl_idname, text="Start", icon = "PLAY")
        if runner.is_running() :            
            row.operator(PARTICLE_FLUIDS_PSToVolumePauseOperator.bl_idname, text="Pause", icon="PAUSE")
        else :
            row.operator(PARTICLE_FLUIDS_PSToVolumeResumeOperator.bl_idname, text="Resume")
        row.operator(ParticleSystemSequenceMeshingCancelOperator.bl_idname, text="Cancel")
        self.layout.separator()

classes = [
    PARTICLE_FLUIDS_PSToVolumeStartOperator,
    PARTICLE_FLUIDS_PSToVolumePauseOperator,
    PARTICLE_FLUIDS_PSToVolumeResumeOperator,
    ParticleSystemSequenceMeshingCancelOperator,
    ParticleSystemSequenceMeshingPanel,
    PARTICLE_FLUIDS_PSToVolumeProperty
]

class PARTICLE_FLUIDS_PSToVolumeUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.meshing_property = bpy.props.PointerProperty(type=PARTICLE_FLUIDS_PSToVolumeProperty)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.meshing_property