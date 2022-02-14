import bpy
from bpy.props import FloatProperty, StringProperty, BoolProperty

from physics.fluid_scene import FluidScene
from ui.bl_fluid import BLFluid

class FluidProperty(bpy.types.PropertyGroup) :
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
  is_static_prop : BoolProperty(
    name="is_static",
    description="Boundary",
    default = False,
  )

class SAMPLE27_OT_Nop(bpy.types.Operator):
    bl_idname = "object.sample27_nop"
    bl_label = "NOP"
    bl_description = "何もしない"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self, context):
      is_active = bpy.context.active_object.ps_fluid.is_active_prop
      bpy.context.active_object.ps_fluid.is_active_prop = not is_active
      return {'FINISHED'}

class PARTICLE_FLUID_PT_FluidPanel(bpy.types.Panel) :
  bl_space_type = "PROPERTIES"
  bl_region_type = "WINDOW"
  bl_context = "physics"
  bl_category = "ParticleFluid"
  bl_label = "ParticleFluid"
 
  def draw(self, context):
    layout = self.layout
    layout.operator(SAMPLE27_OT_Nop.bl_idname, text="ParticleFluid")    
    if bpy.context.active_object.ps_fluid.is_active_prop == True :
      fluid_property = bpy.context.active_object.ps_fluid
#      layout.prop(fluid_property, "is_active_prop", text="Active")
      layout.prop(fluid_property, "particle_radius_prop", text="ParticleRadius")
      layout.prop(fluid_property, "stiffness_prop", text="Stiffness")
      layout.prop(fluid_property, "viscosity_prop", text="Viscosity")
      layout.prop(fluid_property, "is_static_prop", text="Static")
#    for fluid_property in context.scene.fluid_properties :
#      op_del = layout.operator(FluidDeleteOperator.bl_idname, text="Delete")
#      op_del.fluid_name = fluid_property.name_prop

classes = [
  SAMPLE27_OT_Nop,
  FluidProperty,
  PARTICLE_FLUID_PT_FluidPanel,  
]

class PARTICLE_FLUIDS_FluidUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Object.ps_fluid = bpy.props.PointerProperty(name="PSFluid", type=FluidProperty)
#    fluid_prop = bpy.context.scene.fluid_properties.add()
    
  def unregister() :
    del bpy.types.Object.ps_fluid
    for c in classes:
      bpy.utils.unregister_class(c)
 