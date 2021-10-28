import bpy
from bpy.props import FloatProperty

from physics.fluid_scene import FluidScene
from ui.bl_fluid import BLFluid
from ui.model import Model as model

class FluidAddOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidaddoperator"
  bl_label = "FluidAdd"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
    fluid = BLFluid(model.scene)
    fluid.build()
    model.bl_fluids["Fluid01"] = fluid
    context.scene.fluid_properties.add()
    return {'FINISHED'}

class FluidSourceSelectOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidsourceselectoperator"
  bl_label = "Fluid"
  bl_options = {"REGISTER", "UNDO"}
  fluid_name : bpy.props.StringProperty()

  def execute(self, context) :
      selected_mesh = self.get_selected_mesh(context)

      fluid = model.bl_fluids[self.fluid_name]
      fluid.convert_from_polygon_mesh(selected_mesh)
      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

class FluidUpdateOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidupdate"
  bl_label = "Fluid"
  bl_options = {"REGISTER", "UNDO"}
  fluid_name : bpy.props.StringProperty()

  def execute(self, context) :
      fluid = model.bl_fluids[self.fluid_name]
      fluid.build()
      fluid.fluid.particle_radius = context.scene.fluid_properties[0].particle_radius_prop
      fluid.fluid.stiffness = context.scene.fluid_properties[0].stiffness_prop
      fluid.fluid.viscosity = context.scene.fluid_properties[0].viscosity_prop
      fluid.fluid.send()
      return {'FINISHED'}

class FluidProperty(bpy.types.PropertyGroup) :
  name_prop : bpy.props.StringProperty(
    name="name",
    description="Name",
    default="Fluid01"
  )
  stiffness_prop : bpy.props.FloatProperty(
    name="stiffness",
    description="Stiffness",
    default=0.25,
    min = 0.0,
    max = 100.0,
  )
  particle_radius_prop : FloatProperty(
    name="particle_radius",
    description="ParticleRadius",
    default=0.2,
    min=0.0,
    max=100.0,
  )
  viscosity_prop : FloatProperty(
    name="viscosity",
    description="Viscosity",
    default = 10.0,
    min = 0.0,
    max = 100.0,
  )

class FluidPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Fluid"
  
  def draw(self, context):
    layout = self.layout
    layout.operator(FluidAddOperator.bl_idname, text="Add")
    for fluid_property in context.scene.fluid_properties :
      layout.prop(fluid_property, "name_prop", text="Name")
      layout.prop(fluid_property, "particle_radius_prop", text="ParticleRadius")
      layout.prop(fluid_property, "stiffness_prop", text="Stiffness")
      layout.prop(fluid_property, "viscosity_prop", text="Viscosity")
      op_sel = layout.operator(FluidSourceSelectOperator.bl_idname, text="SelectSource")
      op_sel.fluid_name = fluid_property.name_prop
      op_up = layout.operator(FluidUpdateOperator.bl_idname, text="Update")
      op_up.fluid_name = fluid_property.name_prop

classes = [
  FluidAddOperator,
  FluidSourceSelectOperator,
  FluidUpdateOperator,
  FluidProperty,
  FluidPanel,  
]

class FluidUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.fluid_properties = bpy.props.CollectionProperty(type=FluidProperty)
#    fluid_prop = bpy.context.scene.fluid_properties.add()
    
  def unregister() :
    del bpy.types.Scene.fluid_properties
    for c in classes:
      bpy.utils.unregister_class(c)
 