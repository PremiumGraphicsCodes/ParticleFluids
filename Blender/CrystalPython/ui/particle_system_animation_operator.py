import bpy
from ui.model import Model as model
from ui.bl_particle_system import BLParticleSystem

class ParticleSystemAnimationOperator(bpy.types.Operator):
    bl_idname = "pg.particlesystemanimationoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"

    __running = False

    # モーダルモード中はTrueを返す
    @classmethod
    def is_running(self):
        return self.__running

    def modal(self, context, event):
        op = ParticleSystemAnimationOperator
        active_obj = context.active_object

        # エリアを再描画
        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        op = ParticleSystemAnimationOperator

        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not self.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                op.__running = True

                ps = BLParticleSystem(model.scene)
                ps.convert_to_polygon_mesh("")               
                ps.ps.create_empty("")

                print("animation start")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                op.__running = False
                print("animation stop")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}

# UI
class ParticleSystemAnimationPanel(bpy.types.Panel):
    bl_label = "Start"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Animation"
    bl_context = "objectmode"

    def draw(self, context):
        op = ParticleSystemAnimationOperator
        if not op.is_running():
            self.layout.operator(op.bl_idname,text="開始", icon='PLAY')
        else:
            self.layout.operator(op.bl_idname,text="終了", icon='PAUSE')
