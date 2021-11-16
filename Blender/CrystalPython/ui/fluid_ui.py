import bpy
from bpy.props import FloatProperty, StringProperty, BoolProperty

from physics.fluid_scene import FluidScene
from ui.bl_fluid import BLFluid
from ui.model import Model as model

def find_fluid_prop_by_name(context, name) :
  for prop in context.scene.fluid_properties :
    if prop.name_prop == name :
      return prop 

class FluidAddOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidaddoperator"
  bl_label = "FluidAdd"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
    fluid = BLFluid(model.scene)
    fluid.build()
    #fluid.convert_to_polygon_mesh("Fluid01")
    model.bl_fluids["Fluid01"] = fluid
    prop = context.scene.fluid_properties.add()
    prop.name_prop = "Fluid01"
    selected_mesh = self.get_selected_mesh(context)
    fluid.convert_from_polygon_mesh(selected_mesh)
    fluid.convert_to_polygon_mesh("Fluid01")
    return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

class FluidDeleteOperator(bpy.types.Operator):
    bl_idname = "pg.fluiddeleteoperator"
    bl_label = "Delete"
    bl_description = "Hello"
    fluid_name : StringProperty()

    def execute(self, context) :
        fluid = model.bl_fluids[self.fluid_name]
        model.scene.delete( fluid.fluid.id, False )
        del fluid
        index = 0
        for fluid_property in context.scene.fluid_properties :
            if fluid_property.name_prop == self.fluid_name :
                context.scene.fluid_properties.remove(index)
                break
            index+=1

        return {'FINISHED'}    

class FluidUpdateOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidupdate"
  bl_label = "Fluid"
  bl_options = {"REGISTER", "UNDO"}
  fluid_name : bpy.props.StringProperty()

  def execute(self, context) :
      fluid = model.bl_fluids[self.fluid_name]
      prop = find_fluid_prop_by_name(context, self.fluid_name)
      fluid.fluid.particle_radius = prop.particle_radius_prop
      fluid.fluid.stiffness = prop.stiffness_prop
      fluid.fluid.viscosity = prop.viscosity_prop
      fluid.fluid.is_boundary = prop.is_static_prop
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
  is_static_prop : BoolProperty(
    name="is_static",
    description="Boundary",
    default = False,
  )

class FluidPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "PFFluid"
  bl_label = "Fluid"
  
  def draw(self, context):
    layout = self.layout
    layout.operator(FluidAddOperator.bl_idname, text="Add")
    for fluid_property in context.scene.fluid_properties :
      layout.prop(fluid_property, "name_prop", text="Name")
      layout.prop(fluid_property, "particle_radius_prop", text="ParticleRadius")
      layout.prop(fluid_property, "stiffness_prop", text="Stiffness")
      layout.prop(fluid_property, "viscosity_prop", text="Viscosity")
      layout.prop(fluid_property, "is_static_prop", text="Static")
      op_up = layout.operator(FluidUpdateOperator.bl_idname, text="Update")
      op_up.fluid_name = fluid_property.name_prop
      op_del = layout.operator(FluidDeleteOperator.bl_idname, text="Delete")
      op_del.fluid_name = fluid_property.name_prop

classes = [
  FluidAddOperator,
  FluidDeleteOperator,
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
 