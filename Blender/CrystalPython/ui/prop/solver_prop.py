import bpy

from bpy.props import (
    BoolProperty,
    IntProperty,
    FloatProperty,
    FloatVectorProperty,
)

class PARTICLE_FLUIDS_SolverProperty(bpy.types.PropertyGroup) :
    is_active_prop : BoolProperty(
        name ="active",
        description = "Active",
        default = False,
    )
    start_frame_prop : IntProperty(
        name = "start_frame",
        description="StartFrame",
        default=0,
        min=0,
    )
    end_frame_prop : IntProperty(
        name = "end_frame",
        description="EndFrame",
        default=250,
        min=0,
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
        default=(0.0, 0.0, -9.8)
    )
    search_radius_prop : FloatProperty(
        name="search_radius",
        description="SearchRadius",
        default = 3.0,
        min = 0.0
    )
#    min : bpy.props.FloatVectorProperty(
#        name="min",
#        description="Min",
#        default=(-1.0, -1.0, -1.0)
#    )
#    max : bpy.props.FloatVectorProperty(
#        name="max",
#        description="Max",
#        default=(1.0, 1.0, 1.0)
#    )
    export_dir_path : bpy.props.StringProperty(
        name="export_dir",
        description="Path to Directory",
        default="C:/tmp",
        maxlen=1024,
        subtype='DIR_PATH',
    )
    iteration_prop : bpy.props.IntProperty(
        name="iteration_prop",
        description ="Iteration",
        default =1,
        min = 1,
    )
    progress_prop : bpy.props.IntProperty(
        name="progress",
        description="Progress",
        default = 0,   
    )
