import bpy
import os

from bpy.props import (
    IntProperty,
    FloatProperty,
    FloatVectorProperty,
    StringProperty
)

from physics.solver_scene import SolverScene
from ui.bl_fluid import BLFluid
from ui.bl_boundary import BLBoundary
from CrystalPLI import Vector3df, Vector3dd, Box3dd
from scene.file_io import FileIO
from ui.bl_solver import BLSolver
from bpy.app.handlers import persistent

from CrystalPLI import World
from scene.scene import Scene

world = World()
scene = Scene(world)

bl_solver = BLSolver()
bl_boundary = None
bl_fluids = []

def find_all_fluids() :
    global scene
    fluids = []
    for o in bpy.data.objects:
        if o.type == 'MESH' and o.ps_fluid.is_active_prop :
            fluid = BLFluid(scene)
            fluid.build(scene)
            fluid.convert_from_polygon_mesh(o.to_mesh())
            fluid.reset(o.ps_fluid)
            fluids.append(fluid)
    return fluids

class SolverUpdateOperator(bpy.types.Operator):
    bl_idname = "pg.solverupdateoperator"
    bl_label = "Delete"
    bl_description = "Hello"
    solver_name : StringProperty()
    
    def execute(self, context) :
        global scene
        global solver
        bl_solver.build(scene)
        bl_solver.reset()

        global bl_fluids
        bl_fluids = find_all_fluids()

        for bl_fluid in bl_fluids :
            bl_solver.add_fluid(bl_fluid)

        global bl_boundary
        if bl_boundary == None :
            bl_boundary = BLBoundary(scene)
            bl_boundary.build(scene)

        min = context.scene.solver_property.min
        max = context.scene.solver_property.max
        bl_boundary.boundary.bounding_box = Box3dd(Vector3dd(min[0],min[1],min[2]), Vector3dd(max[0],max[1],max[2]))
        bl_boundary.boundary.send()
        bl_solver.add_boundary(bl_boundary)

        bl_solver.send()
        bl_solver.set_iteration( context.scene.solver_property.iteration_prop )
        bl_solver.set_export_path( context.scene.solver_property.export_dir_path )
        return {'FINISHED'}


@persistent
def on_frame_changed_solver(scene):
    global bl_solver
    print("OnChangedFrame")
    if bl_solver.is_running() :
        print("OnRunSolver")
        bl_solver.step(scene.frame_current)

class SolverStartOperator(bpy.types.Operator):
    bl_idname = "pg.solverstartoperator"
    bl_label = "SolverStart"
    bl_description = "Hello"

    def execute(self, context) :
        if not bl_solver.is_running() :
            bl_solver.start()
        else :
            bl_solver.stop()
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
    min : bpy.props.FloatVectorProperty(
        name="min",
        description="Min",
        default=(-1.0, -1.0, -1.0)
    )
    max : bpy.props.FloatVectorProperty(
        name="max",
        description="Max",
        default=(1.0, 1.0, 1.0)
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
        global bl_solver
        solver_property = context.scene.solver_property
        self.layout.prop(solver_property, "name_prop", text="Name")
        self.layout.prop(solver_property, "time_step_prop", text="TimeStep")
        self.layout.prop(solver_property, "external_force_prop", text="ExternalForce")
        self.layout.prop(solver_property, "min", text="Min")
        self.layout.prop(solver_property, "max", text="Max")
        self.layout.prop(solver_property, "export_dir_path", text="ExportPath")
        self.layout.prop(solver_property, "iteration_prop", text="Iteration")
        self.layout.operator(SolverUpdateOperator.bl_idname, text="Reset")
        if not bl_solver.is_running() :
            self.layout.operator(SolverStartOperator.bl_idname,text="Start", icon='PLAY')
        else :
            self.layout.operator(SolverStartOperator.bl_idname,text="Stop", icon='PAUSE')

classes = [
    SolverStartOperator,
    SolverUpdateOperator,
    SolverPanel,
    SolverProperty,
]

def draw_boundary() :
    global bl_fluids
    global bl_boundary
    for bl_fluid in bl_fluids :
        bl_fluid.render()
    if bl_boundary != None :
        bl_boundary.draw()

class SolverUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.solver_property = bpy.props.PointerProperty(type=SolverProperty)
        bpy.app.handlers.frame_change_pre.append(on_frame_changed_solver)
        bpy.types.SpaceView3D.draw_handler_add(draw_boundary, (), 'WINDOW', 'POST_VIEW')

    def unregister():
        #Model.scene.clear(0)
        #Model.scene.clear(1)

        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.solver_property
