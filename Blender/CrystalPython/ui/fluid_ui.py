import bpy
from bpy.props import FloatProperty, StringProperty, BoolProperty

from physics.fluid_scene import FluidScene
from ui.model.bl_fluid import BLFluid
from ui.prop.emitter_prop import PARTICLE_FLUID_EmitterProperty
from ui.prop.fluid_prop import PARTICLE_FLUID_FluidProperty

class PARTICLE_FLUID_OT_Activate(bpy.types.Operator):
    bl_idname = "object.sample27_nop"
    bl_label = "NOP"
    bl_description = "何もしない"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self, context):
      is_active = bpy.context.active_object.ps_fluid.is_active_prop
      bpy.context.active_object.ps_fluid.is_active_prop = not is_active
      return {'FINISHED'}

class PARTICLE_FLUID_OT_Emitter_Activate(bpy.types.Operator):
    bl_idname = "pf.emitteractivate"
    bl_label = "NOP"
    bl_description = "何もしない"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self, context):
      is_active = bpy.context.active_object.ps_emitter.is_active_prop
      bpy.context.active_object.ps_emitter.is_active_prop = not is_active
      return {'FINISHED'}

class PARTICLE_FLUID_PT_FluidPanel(bpy.types.Panel) :
  bl_space_type = "PROPERTIES"
  bl_region_type = "WINDOW"
  bl_context = "physics"
  bl_category = "ParticleFluid"
  bl_label = "ParticleFluid"
 
  def draw(self, context):
    layout = self.layout
    layout.operator(PARTICLE_FLUID_OT_Activate.bl_idname, text="PFFluid")    
    if bpy.context.active_object.ps_fluid.is_active_prop == True :
      fluid_property = bpy.context.active_object.ps_fluid
#      layout.prop(fluid_property, "is_active_prop", text="Active")
      layout.prop(fluid_property, "particle_radius_prop", text="ParticleRadius")
      layout.prop(fluid_property, "stiffness_prop", text="Stiffness")
      layout.prop(fluid_property, "viscosity_prop", text="Viscosity")
      layout.prop(fluid_property, "is_static_prop", text="Static")
    layout.operator(PARTICLE_FLUID_OT_Emitter_Activate.bl_idname, text="PFEmitter")    
    if bpy.context.active_object.ps_emitter.is_active_prop == True :
      fluid_property = bpy.context.active_object.ps_emitter
      layout.prop(fluid_property, "particle_radius_prop", text="ParticleRadius")
      layout.prop(fluid_property, "stiffness_prop", text="Stiffness")
      layout.prop(fluid_property, "viscosity_prop", text="Viscosity")
      layout.prop(fluid_property, "start_step_prop", text="StartStep")
      layout.prop(fluid_property, "end_step_prop", text="EndStep")
      layout.prop(fluid_property, "interval_prop", text="Interval")
      layout.prop(fluid_property, "initial_velocity_prop", text="Velocity")


classes = [
  PARTICLE_FLUID_OT_Activate,
  PARTICLE_FLUID_FluidProperty,
  PARTICLE_FLUID_PT_FluidPanel,  
  PARTICLE_FLUID_OT_Emitter_Activate,
  PARTICLE_FLUID_EmitterProperty,
]

class PARTICLE_FLUIDS_FluidUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Object.ps_fluid = bpy.props.PointerProperty(name="PSFluid", type=PARTICLE_FLUID_FluidProperty)
    bpy.types.Object.ps_emitter = bpy.props.PointerProperty(name="PSEmitter", type=PARTICLE_FLUID_EmitterProperty)
    
  def unregister() :
    del bpy.types.Object.ps_emitter
    del bpy.types.Object.ps_fluid
    for c in classes:
      bpy.utils.unregister_class(c)
 