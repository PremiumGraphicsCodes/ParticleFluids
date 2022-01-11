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
from bpy.app.handlers import persistent

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
        solver.set_iteration( context.scene.solver_property.iteration_prop )
        solver.set_export_path( context.scene.solver_property.export_dir_path )
        return {'FINISHED'}

@persistent
def on_frame_changed_solver(scene):
    print("OnChangedFrame")
    if model.bl_solver.is_running() :
        print("OnRunSolver")
        model.bl_solver.step(scene.frame_current)

class SolverStartOperator(bpy.types.Operator):
    bl_idname = "pg.solverstartoperator"
    bl_label = "SolverStart"
    bl_description = "Hello"

    def execute(self, context) :
        if not model.bl_solver.is_running() :
            model.bl_solver.start()
        else :
            model.bl_solver.stop()
        return {'FINISHED'}

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
    iteration_prop : bpy.props.IntProperty(
        name="iteration_prop",
        description ="Iteration",
        default =1,
        min = 1,
    )

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
        self.layout.prop(solver_property, "iteration_prop", text="Iteration")
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
        bpy.app.handlers.frame_change_pre.append(on_frame_changed_solver)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.solver_property
