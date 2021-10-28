import bpy
from bpy.props import FloatProperty, FloatVectorProperty

from physics.fluid_scene import FluidScene
from ui.bl_boundary import BLBoundary

from ui.model import Model as model
from CrystalPLI import Vector3dd, Box3dd

class BoundaryAddOperator(bpy.types.Operator) :
  bl_idname = "pg.boundaryadd"
  bl_label = "Add"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
    boundary = BLBoundary(model.scene)
    boundary.build()
    boundary.boundary.name = "Boundary01"
    boundary.boundary.send()
    context.scene.boundary_properties.add()
    model.bl_boundaries["Boundary01"] = boundary
    return {'FINISHED'}

class BoundaryUpdateOperator(bpy.types.Operator) :
  bl_idname = "pg.boundaryupdate"
  bl_label = "Update"
  bl_options = {"REGISTER", "UNDO"}
  boundary_name : bpy.props.StringProperty()

  def execute(self, context) :
      boundary = model.bl_boundaries[self.boundary_name]
      min = context.scene.boundary_properties[0].min
      max = context.scene.boundary_properties[0].max
      v1 = Vector3dd(min[0], min[1], min[2])
      v2 = Vector3dd(max[0], max[1], max[2])
      bb = Box3dd(v1, v2)
      boundary.boundary.bounding_box = bb
      boundary.boundary.send()
      return {'FINISHED'}

class BoundaryDeleteOperator(bpy.types.Operator) :
  bl_idname = "pg.boundarydelete"
  bl_label = "Add"
  bl_options = {"REGISTER", "UNDO"}
  boundary_name : bpy.props.StringProperty()

  def execute(self, context) :
    boundary = model.bl_boundaries[self.boundary_name]
    model.scene.delete(boundary.boundary.id, False)
    del boundary
    index = 0
    for boundary_property in context.scene.boundary_properties :
      if boundary_property.name == self.boundary_name :
        context.scene.boundary_properties.remove(index)
        break
      index+=1
    return {'FINISHED'}

class BoundaryPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Boundary"
  
  def draw(self, context):
    layout = self.layout
    #layout.prop(context.scene, "min_prop", text="Min")
    #row = layout.row()
    for boundary_property in context.scene.boundary_properties :
      layout.prop(boundary_property, "name", text="Name")
      layout.prop(boundary_property, "min", text="Min")
      layout.prop(boundary_property, "max", text="Max")
      op = layout.operator(BoundaryUpdateOperator.bl_idname, text="Update")
      op.boundary_name = boundary_property.name
      op2 = layout.operator(BoundaryDeleteOperator.bl_idname, text="Delete")
      op2.boundary_name = boundary_property.name
    layout.operator(BoundaryAddOperator.bl_idname, text="Add")

class BoundaryProperty(bpy.types.PropertyGroup) :
  name : bpy.props.StringProperty(
    name = "name",
    description="Name",
    default = "Boundary01"
  )
  min : bpy.props.FloatVectorProperty(
        name="min",
        description="Min",
        default=(0.0, 0.0, 0.0)
    )
  max : bpy.props.FloatVectorProperty(
        name="max",
        description="Max",
        default=(1.0, 1.0, 1.0)
    )

classes = [
  BoundaryAddOperator,
  BoundaryDeleteOperator,
  BoundaryProperty,
  BoundaryUpdateOperator,
  BoundaryPanel,
]

class BoundaryUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.boundary_properties = bpy.props.CollectionProperty(type=BoundaryProperty)

  def unregister() :
    del bpy.types.Scene.boundary_properties
    for c in classes:
      bpy.utils.unregister_class(c)
