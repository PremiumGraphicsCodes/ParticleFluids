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
    boundary.boundary.bounding_box = Box3dd(Vector3dd(-1,-1,-1), Vector3dd(1,1,1))
    boundary.boundary.send()
    boundary.convert_to_polygon_mesh("Boundary01")
    boundary.prop = context.scene.boundary_properties.add()
    model.bl_boundaries["Boundary01"] = boundary
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
        default=(-1.0, -1.0, -1.0)
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
  BoundaryPanel,
]

import bpy
import gpu
from gpu_extras.batch import batch_for_shader

coords = [(1, 1, 1), (-2, 0, 0), (-2, -1, 3), (0, 1, 1)]
shader = gpu.shader.from_builtin('3D_UNIFORM_COLOR')
batch = batch_for_shader(shader, 'LINES', {"pos": coords})

def draw():
    shader.bind()
    shader.uniform_float("color", (1, 1, 0, 1))
    batch.draw(shader)

class BoundaryUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.boundary_properties = bpy.props.CollectionProperty(type=BoundaryProperty)
    bpy.types.SpaceView3D.draw_handler_add(draw, (), 'WINDOW', 'POST_VIEW')

  def unregister() :
    del bpy.types.Scene.boundary_properties
    for c in classes:
      bpy.utils.unregister_class(c)
