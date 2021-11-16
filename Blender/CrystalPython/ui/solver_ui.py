import bpy
import os

from bpy.props import (
    IntProperty,
    FloatProperty,
    FloatVectorProperty,
    StringProperty
)

from ui.model import Model as model
from physics.solver_scene import SolverScene
from ui.bl_fluid import BLFluid
from ui.bl_boundary import BLBoundary
from CrystalPLI import Vector3df
from scene.file_io import FileIO

from ui.bl_solver import BLSolver

def find_fluid_prop_by_name(context, name) :
  for prop in bpy.context.scene.fluid_properties :
    if prop.name_prop == name :
      return prop 


class SolverUpdateOperator(bpy.types.Operator):
    bl_idname = "pg.solverupdateoperator"
    bl_label = "Delete"
    bl_description = "Hello"
    solver_name : StringProperty()
    
    def execute(self, context) :
        solver = model.bl_solver
        solver.reset()
        for bl_fluid in model.bl_fluids.values() :
            bl_fluid.reset()
            solver.add_fluid(bl_fluid)
        for bl_boundary in model.bl_boundaries.values() :
            bl_boundary.reset()
            solver.add_boundary(bl_boundary)
        solver.send()
        solver.export_dir_path = context.scene.solver_property.export_dir_path
        return {'FINISHED'}

class SolverStartOperator(bpy.types.Operator):
    bl_idname = "pg.solverstartoperator"
    bl_label = "SolverStart"
    bl_description = "Hello"

    def modal(self, context, event):
        solver = model.bl_solver
        if solver.is_running() :
            solver.step(bpy.context.scene.frame_current)

        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        solver = model.bl_solver
        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not solver.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                solver.start()

                print("simulation start")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                solver.stop()
                print("simulation stop")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}

class SolverProperty(bpy.types.PropertyGroup) :
    name_prop : StringProperty(
        name="name",
        description="Name",
        default="Solver01"
    )
    time_step_prop : FloatProperty(
        name="time_step",
        description="TimeStep",
        default=0.01,
        min=0.0,
        max=1.0,
    )
    external_force_prop : FloatVectorProperty(
        name="external_force",
        description="ExternalForce",
        default=(0.0, 0.0, -9.8),
        min=-100.0,
        max=100.0,
    )
    export_dir_path : bpy.props.StringProperty(
        name="export_dir",
        description="Path to Directory",
        default="tmp_txt",
        maxlen=1024,
        subtype='DIR_PATH',
    )

# UI
class SolverPanel(bpy.types.Panel):
    bl_label = "Solver"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "PFSolver"
    bl_context = "objectmode"

    def draw(self, context):
        solver_property = context.scene.solver_property
        self.layout.prop(solver_property, "name_prop", text="Name")
        self.layout.prop(solver_property, "time_step_prop", text="TimeStep")
        self.layout.prop(solver_property, "external_force_prop", text="ExternalForce")
        self.layout.prop(solver_property, "export_dir_path", text="ExportPath")
        self.layout.operator(SolverUpdateOperator.bl_idname, text="Reset")
        if not model.bl_solver.is_running() :
            self.layout.operator(SolverStartOperator.bl_idname,text="Start", icon='PLAY')
        else :
            self.layout.operator(SolverStartOperator.bl_idname,text="Stop", icon='PAUSE')

classes = [
    SolverStartOperator,
    SolverUpdateOperator,
    SolverPanel,
    SolverProperty,
]

class SolverUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.solver_property = bpy.props.PointerProperty(type=SolverProperty)
        model.bl_solver = BLSolver()
        model.bl_solver.build()

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.solver_property