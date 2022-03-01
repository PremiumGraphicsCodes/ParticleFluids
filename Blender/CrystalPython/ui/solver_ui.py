import bpy

from physics.solver_scene import SolverScene
from ui.model.bl_fluid import BLFluid
from ui.model.bl_emitter import BLEmitter
from ui.model.bl_boundary import BLBoundary
from ui.prop.solver_prop import PARTICLE_FLUIDS_SolverProperty
from CrystalPLI import Vector3df, Vector3dd, Box3dd
from scene.file_io import FileIO
from ui.model.bl_solver import BLSolver
#from bpy.app.handlers import persistent

from CrystalPLI import World
from scene.scene import Scene
from ui.shader.point_shader import PointShader

world = World()
scene = Scene(world)

shader = PointShader()
bl_solver = BLSolver()

def find_all_fluids() :
    fluids = []
    for o in bpy.data.objects:
        if o.type == 'MESH' and o.ps_fluid.is_active_prop :
            fluid = BLFluid(scene)
            fluid.build(scene)
            fluid.convert_from_polygon_mesh(o.to_mesh())
            fluid.reset(o.ps_fluid)
            fluids.append(fluid)
    return fluids

def find_all_emitters() :
    emitters = []
    for o in bpy.data.objects:
        if o.type == 'MESH' and o.ps_emitter.is_active_prop :
            fluid = BLEmitter(scene)
            fluid.build(scene)
            fluid.convert_from_polygon_mesh(o.to_mesh())
            fluid.reset(o.ps_emitter)
            emitters.append(fluid)
    return emitters

def reset() :
    if not shader.exists() :
        shader.build(scene)

    bl_solver.build(scene)
    bl_solver.reset()

    bl_fluids = find_all_fluids()

    for bl_fluid in bl_fluids :
        bl_solver.add_fluid(bl_fluid)

    bl_emitters = find_all_emitters()

    for bl_emitter in bl_emitters :
        bl_solver.add_emitter(bl_emitter)

    bl_boundary = BLBoundary(scene)
    bl_boundary.build(scene)

    min = bpy.context.scene.solver_property.min
    max = bpy.context.scene.solver_property.max
    bl_boundary.set_box( Box3dd(Vector3dd(min[0],min[1],min[2]), Vector3dd(max[0],max[1],max[2])) )
    bl_boundary.send()
    bl_solver.add_boundary(bl_boundary)
    bl_solver.set_effect_length(bpy.context.scene.solver_property.search_radius_prop)
    
    bl_solver.send()
    bl_solver.set_start_frame(bpy.context.scene.solver_property.start_frame_prop)
    bl_solver.set_end_frame(bpy.context.scene.solver_property.end_frame_prop)
    bl_solver.set_iteration( bpy.context.scene.solver_property.iteration_prop )
    bl_solver.set_export_path( bpy.context.scene.solver_property.export_dir_path )

class PARTICLE_FLUIDS_OT_SolverStartOperator(bpy.types.Operator):
    bl_idname = "pf.solverstartoperator"
    bl_label = "SolverStart"
    bl_description = "Hello"

    def execute(self, context) :
        reset()
        bl_solver.start()
        return {'FINISHED'}

class PARTICLE_FLUIDS_OT_SolverPauseOperator(bpy.types.Operator):
    bl_idname = "pf.solverpauseoperator"
    bl_label = "SolverPause"
    bl_description = "Hello"

    def execute(self, context) :
        bl_solver.pause()
        return {'FINISHED'}

class PARTICLE_FLUIDS_OT_SolverResumeOperator(bpy.types.Operator):
    bl_idname = "pf.solverresumeoperator"
    bl_label = "SolverResume"
    bl_description = "Hello"

    def execute(self, context) :
        bl_solver.resume()
        return {'FINISHED'}

class PARTICLE_FLUIDS_OT_SolverCancelOperator(bpy.types.Operator):
    bl_idname = "pf.solvercanceloperator"
    bl_label = "SolverCancel"
    bl_description = "Hello"

    def execute(self, context) :
        bl_solver.stop()
        return {'FINISHED'}        

class PARTICLE_FLUIDS_PT_SolverPanel(bpy.types.Panel):
    bl_label = "Solver"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "PFSolver"
    bl_context = "objectmode"

    def draw(self, context):
        global bl_solver
        solver_property = context.scene.solver_property
        self.layout.prop(solver_property, "is_active_prop", text="Render")
        self.layout.prop(solver_property, "start_frame_prop", text="StartFrame")
        self.layout.prop(solver_property, "end_frame_prop", text="EndFrame")
        self.layout.prop(solver_property, "time_step_prop", text="TimeStep")
        self.layout.prop(solver_property, "external_force_prop", text="ExternalForce")
        self.layout.prop(solver_property, "search_radius_prop", text="SearchRadius")
        self.layout.prop(solver_property, "min", text="Min")
        self.layout.prop(solver_property, "max", text="Max")
        self.layout.prop(solver_property, "export_dir_path", text="ExportPath")
        self.layout.prop(solver_property, "iteration_prop", text="Iteration")

        self.layout.separator()
        row = self.layout.row(align=False)
        row.operator(PARTICLE_FLUIDS_OT_SolverStartOperator.bl_idname,text="Start", icon='PLAY')
        if bl_solver.is_running() :
            row.operator(PARTICLE_FLUIDS_OT_SolverPauseOperator.bl_idname,text="Pause", icon='PAUSE')
        else :            
            row.operator(PARTICLE_FLUIDS_OT_SolverResumeOperator.bl_idname, text="Resume")
        row.operator(PARTICLE_FLUIDS_OT_SolverCancelOperator.bl_idname,text="Cancel", icon='PAUSE')
        self.layout.separator()

classes = [
    PARTICLE_FLUIDS_OT_SolverStartOperator,
    PARTICLE_FLUIDS_OT_SolverPauseOperator,
    PARTICLE_FLUIDS_OT_SolverResumeOperator,
    PARTICLE_FLUIDS_OT_SolverCancelOperator,
    PARTICLE_FLUIDS_PT_SolverPanel,
    PARTICLE_FLUIDS_SolverProperty,
]

def on_draw_solver() :
    #global bl_solver
    if bl_solver.is_running() :
        bpy.context.scene.frame_current = bl_solver.get_current_frame()

    #bpy.context.scene.solver_property.progress_prop = bl_solver.get_current_frame()
    if bpy.context.scene.solver_property.is_active_prop :
        bl_solver.render(shader.get_shader())

class SolverUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.solver_property = bpy.props.PointerProperty(type=PARTICLE_FLUIDS_SolverProperty)
        bpy.types.SpaceView3D.draw_handler_add(on_draw_solver, (), 'WINDOW', 'POST_VIEW')

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.solver_property
