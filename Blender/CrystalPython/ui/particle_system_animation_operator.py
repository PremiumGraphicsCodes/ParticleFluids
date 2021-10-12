import bpy
from ui.model import Model as model
from ui.bl_particle_system import BLParticleSystem
from CrystalPLI import Vector3dd, Vector3ddVector

class ParticleSystemAnimator :
    def __init__(self) :
        self.ps = None
        self.__running = False
        self.positions = Vector3ddVector()
        self.positions.add(Vector3dd(0,0,0))

    def init(self):
        if self.ps == None :
            self.ps = BLParticleSystem(model.scene)
            self.ps.ps.create_empty("")
            self.ps.ps.set_positions(self.positions)
            self.ps.convert_to_polygon_mesh("")               

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self):
        self.positions = Vector3ddVector()
        self.positions.add(Vector3dd(10,0,0))
        self.ps.ps.set_positions(self.positions)
        self.ps.update()

    def is_running(self):
        return self.__running


animator = ParticleSystemAnimator()

class ParticleSystemAnimationOperator(bpy.types.Operator):
    bl_idname = "pg.particlesystemanimationoperator"
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

# UI
class ParticleSystemAnimationPanel(bpy.types.Panel):
    bl_label = "Start"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Animation"
    bl_context = "objectmode"

    def draw(self, context):
        op = ParticleSystemAnimationOperator
        if not animator.is_running():
            self.layout.operator(op.bl_idname,text="開始", icon='PLAY')
        else:
            self.layout.operator(op.bl_idname,text="終了", icon='PAUSE')
