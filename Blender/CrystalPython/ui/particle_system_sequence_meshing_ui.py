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
import os
import glob

class MeshingRunner :
    def __init__(self) :
        self.__is_running = False
        self.__frame = 0

    def start(self) :
        self.__is_running = True

    def stop(self) :
        self.__is_running = False

    def step(self, frame) :
        if frame == self.__frame :
            return
        prop = bpy.context.scene.meshing_property
        input_path = prop.input_path_prop
        output_path = prop.output_path_prop
        cell_length = prop.cell_length_prop
        effect_length = prop.effect_length_prop

        # TODO ファイル一覧の取得
        file_path = os.path.join(input_path, "test" + str(frame) + ".txt")
        ps = ParticleSystemScene(model.scene)
        ps.create_empty("")
        FileIO.import_txt(model.scene, ps.id, file_path)
        
        mesh = TriangleMeshScene(model.scene)
        mesh.create_empty("")
            
        builder = SurfaceBuilder(model.scene)
        builder.build_anisotorpic(ps.id, mesh.id, cell_length, effect_length)

        basename_without_ext = os.path.splitext(os.path.basename(file_path))[0]
        export_file_path = os.path.join(output_path, basename_without_ext + ".stl")
        mesh.export_stl(export_file_path)

#            FileIO.ex
            #mesh.convert_to_polygon_mesh("")
        model.scene.delete(ps.id, False)
        model.scene.delete(mesh.id, False)
        self.__frame = frame

    def is_running(self) :
        return self.__is_running

runner = MeshingRunner()

class ParticleSystemSequenceMeshingOperator(bpy.types.Operator) :
    bl_idname = "pg.particlesystemsequencemeshingoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"
    
    def modal(self, context, event):
        if runner.is_running() :
            runner.step(bpy.context.scene.frame_current)

        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not runner.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                runner.start()

                print("simulation start")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                runner.stop()
                print("simulation stop")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}

    def execute(self, context) :

        return {'FINISHED'}


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
        
    cell_length_prop : bpy.props.FloatProperty(
        name="cell_length",
        description="CellLength",
        default=1.0,
        min = 0.0,
        max = 100.0,
        )
        
    effect_length_prop : bpy.props.FloatProperty(
        name="effect_length",
        description="EffectLength",
        default=2.0,
        min=0.0,
        max=100.0,
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
        self.layout.prop(prop, "output_path_prop", text="OutputPath")
        self.layout.prop(prop, "cell_length_prop", text="CellLength")
        self.layout.prop(prop, "effect_length_prop", text="EffectLength")
        #if not runner.is_running() :
        self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname, text="Start", icon = "PLAY")
        #else :
        #    self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname,text="Stop", icon='PAUSE')

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