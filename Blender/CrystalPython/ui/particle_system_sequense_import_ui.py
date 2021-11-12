import bpy
from ui.model import Model as model
from ui.bl_particle_system import BLParticleSystem
from CrystalPLI import Vector3dd, Vector3ddVector
from scene.file_io import FileIO
import os

class ParticleSystemSequenceImporter :
    def __init__(self) :
        self.ps = None
        self.__running = False

    def init(self):
        if self.ps == None :
            self.ps = BLParticleSystem(model.scene)
            self.ps.ps.create_empty("")
            self.ps.convert_to_polygon_mesh("")               

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self):
        time_step = bpy.context.scene.frame_current
        file_path = os.path.join("tmp_txt", "test" + str(time_step) + ".txt")

        FileIO.import_txt(model.scene, self.ps.ps.id, file_path)
        self.ps.update()

    def is_running(self):
        return self.__running

animator = ParticleSystemSequenceImporter()

class ParticleSystemSequenceImportOperator(bpy.types.Operator):
    bl_idname = "pg.particlesystemsequenceimportoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"

    def modal(self, context, event):
        active_obj = context.active_object

        if animator.is_running() :
            animator.step()

        # エリアを再描画
        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not animator.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                animator.init()
                animator.start()

                print("animation start")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                animator.stop()
                print("animation stop")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}


class ParticleSystemSequenceImportPanel(bpy.types.Panel):
    bl_label = "PSSeqImport"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "PFTools"
    bl_context = "objectmode"

    def draw(self, context):
        op = ParticleSystemSequenceImportOperator
        if not animator.is_running():
            self.layout.operator(op.bl_idname,text="ImportStart", icon='PLAY')
        else:
            self.layout.operator(op.bl_idname,text="ImportStop", icon='PAUSE')

classes = [
  ParticleSystemSequenceImportOperator,
  ParticleSystemSequenceImportPanel,
]

class ParticleSystemSequenceImportUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)