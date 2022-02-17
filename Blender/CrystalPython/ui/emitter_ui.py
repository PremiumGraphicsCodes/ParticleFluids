import bpy
from bpy.props import IntProperty, FloatProperty, BoolProperty

#from physics.fluid_scene import FluidScene
from ui.bl_emitter import BLEmitter

class PARTICLE_FLUID_EmitterProperty(bpy.types.PropertyGroup) :
  is_active_prop : BoolProperty(
    name="is_active",
    description="Active",
    default = False,
  )
  stiffness_prop : bpy.props.FloatProperty(
    name="stiffness",
    description="Stiffness",
    default=100.0,
    min = 0.0,
  )
  particle_radius_prop : FloatProperty(
    name="particle_radius",
    description="ParticleRadius",
    default=1.0,
    min=0.0,
  )
  viscosity_prop : FloatProperty(
    name="viscosity",
    description="Viscosity",
    default = 10.0,
    min = 0.0,
  )
  start_step_prop : IntProperty(
    name="start_step",
    description="StartStep",
    default=1,
    min=0
  )
  end_step_prop : IntProperty(
    name="end_step",
    description="EndStep",
    default=100,
    min=0
  )
  interval_prop : IntProperty(
    name="interval",
    description="Interval",
    default=5,
    min=1
  )

class PARTICLE_FLUID_OT_Emitter_Activate(bpy.types.Operator):
    bl_idname = "pf.emitteractivate"
    bl_label = "NOP"
    bl_description = "何もしない"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self, context):
      is_active = bpy.context.active_object.ps_emitter.is_active_prop
      bpy.context.active_object.ps_emitter.is_active_prop = not is_active
      return {'FINISHED'}

class PARTICLE_FLUID_PT_EmitterPanel(bpy.types.Panel) :
  bl_space_type = "PROPERTIES"
  bl_region_type = "WINDOW"
  bl_context = "physics"
  bl_category = "ParticleFluid"
  bl_label = "ParticleFluid"
 
  def draw(self, context):
    layout = self.layout
    layout.operator(PARTICLE_FLUID_OT_Emitter_Activate.bl_idname, text="PFEmitter")    
    if bpy.context.active_object.ps_emitter.is_active_prop == True :
      fluid_property = bpy.context.active_object.ps_emitter
      layout.prop(fluid_property, "particle_radius_prop", text="ParticleRadius")
      layout.prop(fluid_property, "stiffness_prop", text="Stiffness")
      layout.prop(fluid_property, "viscosity_prop", text="Viscosity")
      layout.prop(fluid_property, "start_step_prop", text="StartStep")
      layout.prop(fluid_property, "end_step_prop", text="EndStep")
      layout.prop(fluid_property, "interval_prop", text="Interval")
#
classes = [
  PARTICLE_FLUID_OT_Emitter_Activate,
  PARTICLE_FLUID_EmitterProperty,
  PARTICLE_FLUID_PT_EmitterPanel,  
]

class PARTICLE_FLUIDS_EmitterUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Object.ps_emitter = bpy.props.PointerProperty(name="PSEmitter", type=PARTICLE_FLUID_EmitterProperty)
#    fluid_prop = bpy.context.scene.fluid_properties.add()
    
  def unregister() :
    del bpy.types.Object.ps_emitter
    for c in classes:
      bpy.utils.unregister_class(c)
 