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
    #boundary.draw()
    boundary.prop = context.scene.boundary_properties.add()
    return {'FINISHED'}

class BoundaryPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "PFBoundary"
#  bl_category = "ParticleFluids"
  bl_label = "Boundary"
  
  def draw(self, context):
    layout = self.layout
    #layout.prop(context.scene, "min_prop", text="Min")
    #row = layout.row()
    for boundary_property in context.scene.boundary_properties :
      layout.prop(boundary_property, "name", text="Name")
      layout.prop(boundary_property, "min", text="Min")
      layout.prop(boundary_property, "max", text="Max")
    layout.operator(BoundaryAddOperator.bl_idname, text="Add")

class BoundaryProperty(bpy.types.PropertyGroup) :
  name : bpy.props.StringProperty(
    name = "name",
    description="Name",
    default = "Boundary01"
  )

classes = [
  BoundaryAddOperator,
  BoundaryProperty,
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
