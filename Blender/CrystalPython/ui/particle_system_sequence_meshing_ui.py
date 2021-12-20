import bpy
from ui.model import Model as model
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

class MeshingRunner :
    def __init__(self) :
        self.__is_running = False
        self.__bl_mesh = None

    def start(self) :
        self.__is_running = True
        if self.__bl_mesh == None :
            self.__bl_mesh = BLTriangleMesh(model.scene)
            self.__bl_mesh.build("Surface")

    def stop(self) :
        self.__is_running = False

    def step(self, frame) :
        prop = bpy.context.scene.meshing_property

        volume_file_path = os.path.join(prop.input_path_prop, "macro" + str(frame) + ".pcd")
        volume_ps = ParticleSystemScene(model.scene)
        volume_ps.create_empty("")
        FileIO.import_pcd(model.scene, volume_ps.id, volume_file_path)

        mass_file_path = os.path.join(prop.input_path_prop, "micro" + str(frame) + ".pcd")
        mass_ps = ParticleSystemScene(model.scene)
        mass_ps.create_empty("")
        FileIO.import_pcd(model.scene, mass_ps.id, mass_file_path)
        
        self.__bl_mesh.mesh = TriangleMeshScene(model.scene)
        self.__bl_mesh.mesh.create_empty("")
            
        builder = SurfaceBuilder(model.scene)
        builder.build_isotorpic(volume_ps.id, self.__bl_mesh.mesh.id, prop.particle_radius_prop, prop.cell_length_prop, prop.threshold_prop)
        self.__bl_mesh.update()

        if prop.do_export_stl_prop :
#            basename_without_ext = os.path.splitext(os.path.basename(volume_file_path))[0]
            export_file_path = os.path.join(prop.output_path_prop, "mesh" + str(frame) + ".stl") #basename_without_ext + ".stl")
            self.__bl_mesh.mesh.export_stl(export_file_path)

        model.scene.delete(mass_ps.id, False)
        model.scene.delete(volume_ps.id, False)
        model.scene.delete(self.__bl_mesh.mesh.id, False)

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
        default=1.0,
        min = 0.0,
        max = 100.0,
    )

    threshold_prop : bpy.props.FloatProperty(
        name="threshold",
        description="Threshold",
        default=1.0,
        min = 0.0,
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
        self.layout.prop(prop, "threshold_prop", text="Threshold")
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