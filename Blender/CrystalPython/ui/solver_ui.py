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

class SolverAddOperator(bpy.types.Operator):
    bl_idname = "pg.solveraddoperator"
    bl_label = "Add"
    bl_description = "Hello"
    
    def execute(self, context) :
        solver = BLSolver()
        solver.build()
        model.bl_solvers["Solver01"] = solver
        prop = context.scene.solver_properties.add()
        prop.name = "Solver01"
        return {'FINISHED'}

class SolverDeleteOperator(bpy.types.Operator):
    bl_idname = "pg.solverdeleteoperator"
    bl_label = "Delete"
    bl_description = "Hello"
    solver_name : StringProperty()

    def execute(self, context) :
        solver = model.bl_solvers[self.solver_name]
        model.scene.delete( solver.solver.id, False )
        del solver
        index = 0
        for solver_property in context.scene.solver_properties :
            if solver_property.name == self.solver_name :
                context.scene.solver_properties.remove(index)
                break
            index+=1

        return {'FINISHED'}

class SolverUpdateOperator(bpy.types.Operator):
    bl_idname = "pg.solverupdateoperator"
    bl_label = "Delete"
    bl_description = "Hello"
    solver_name : StringProperty()
    
    def execute(self, context) :
        solver = model.bl_solvers[self.solver_name]
        solver.reset()
        for bl_fluid in model.bl_fluids.values() :
            solver.add_fluid(bl_fluid)
        for bl_boundary in model.bl_boundaries.values() :
            solver.add_boundary(bl_boundary)
        solver.send()
        solver.frame = context.scene.solver_properties[0].start_frame_prop
        context.scene.solver_properties[0].current_frame_prop = solver.frame
        return {'FINISHED'}

#class SolverResetOperator(bpy.types.Operator):
#    bl_idname = "pg.solverresetoperator"
#    bl_label = "Reset"
#    bl_description = "Hello"
#    solver_name : StringProperty()
    
#    def execute(self, context) :
#        solver = model.bl_solvers[self.solver_name]
#        solver.reset()
#        for bl_fluid in model.bl_fluids.values() :
#            solver.add_fluid(bl_fluid)
#        for bl_boundary in model.bl_boundaries.values() :
#            solver.add_boundary(bl_boundary)
#        solver.send()
#        return {'FINISHED'}


class SolverStartOperator(bpy.types.Operator):
    bl_idname = "pg.solverstartoperator"
    bl_label = "SolverStart"
    bl_description = "Hello"

    def modal(self, context, event):
        solver = model.bl_solvers["Solver01"]
        if solver.is_running() :
            solver.step()
            context.scene.solver_properties[0].current_frame_prop = solver.frame
            if solver.frame >= context.scene.solver_properties[0].end_frame_prop :
                solver.stop()

        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        solver = model.bl_solvers["Solver01"]
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
    start_frame_prop : IntProperty(
        name="start_frame",
        description="StartFrame",
        default = 1,
        min = 1
    )
    current_frame_prop : IntProperty(
        name="current_frame",
        description="CurrentFrame",
        default = 1,
        min = 1
    )
    end_frame_prop : IntProperty(
        name="end_frame",
        description="EndFrame",
        default = 250,
        min = 1
    )


# UI
class SolverPanel(bpy.types.Panel):
    bl_label = "Solver"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Simulation"
    bl_context = "objectmode"

    def draw(self, context):
        self.layout.operator(SolverAddOperator.bl_idname, text="Add")
        solver = model.bl_solvers["Solver01"]
        for solver_property in context.scene.solver_properties :
#            solver_property.current_frame_prop = solver.frame

            self.layout.prop(solver_property, "name_prop", text="Name")
            self.layout.prop(solver_property, "time_step_prop", text="TimeStep")
            self.layout.prop(solver_property, "external_force_prop", text="ExternalForce")
            self.layout.prop(solver_property, "start_frame_prop", text="StartFrame")
            self.layout.prop(solver_property, "current_frame_prop", text="CurrentFrame")            
            self.layout.prop(solver_property, "end_frame_prop", text="EndFrame")
            self.layout.operator(SolverStartOperator.bl_idname,text="Start", icon='PLAY')
            op_update = self.layout.operator(SolverUpdateOperator.bl_idname, text="Update")
            op_update.solver_name = solver_property.name_prop
            op_del = self.layout.operator(SolverDeleteOperator.bl_idname,text="Delete")
            op_del.solver_name = solver_property.name_prop
            #if not solver.is_running():
            #    self.layout.operator(SolverStartOperator.bl_idname,text="Start", icon='PLAY')
            #else:
            #    self.layout.operator(SolverStartOperator.bl_idname,text="Stop", icon='PAUSE')

classes = [
    SolverAddOperator,
    SolverStartOperator,
    SolverDeleteOperator,
    SolverUpdateOperator,
    SolverPanel,
    SolverProperty,
]

class SolverUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.solver_properties = bpy.props.CollectionProperty(type=SolverProperty)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.solver_properties