import bpy
from ui.model import Model as model

from physics.fluid_scene import FluidScene
from physics.solver_scene import SolverScene

class PhysicsSimulationOperator(bpy.types.Operator):
    bl_idname = "pg.physicssimulationoperator"
    bl_label = "PhysicsSimulation"
    bl_description = "Hello"

    __running = False

    # モーダルモード中はTrueを返す
    @classmethod
    def is_running(cls):
        return cls.__running

    def modal(self, context, event):
        op_cls = PhysicsSimulationOperator
        active_obj = context.active_object

        model.solver.simulate()

        # エリアを再描画
        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        op_cls = PhysicsSimulationOperator

        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not self.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                op_cls.__running = True

                model.solver.create()
                fluid = FluidScene(model.scene)
                fluid.create()
                fluids = []
                fluids.append(fluid)
                model.solver.send(fluids)
                print("サンプル 3-1: オブジェクトの回転処理を開始しました。")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                op_cls.__running = False
                print("サンプル 3-1: オブジェクトの回転処理を終了しました。")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}

# UI
class PhysicsSimulationPanel(bpy.types.Panel):
    bl_label = "Start"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Simulation"
    bl_context = "objectmode"

    def draw(self, context):
        op_cls = PhysicsSimulationOperator
        layout = self.layout
        # [開始] / [終了] ボタンを追加
        if not op_cls.is_running():
            layout.operator(op_cls.bl_idname,text="開始", icon='PLAY')
        else:
            layout.operator(op_cls.bl_idname,text="終了", icon='PAUSE')
