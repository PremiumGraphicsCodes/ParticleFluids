import bpy
from bpy.props import FloatProperty, FloatVectorProperty

from physics.fluid_scene import FluidScene
from ui.bl_boundary import BLBoundary

from ui.model import Model as model
from CrystalPLI import Vector3dd, Box3dd

boundary = BLBoundary(model.scene)

class BoundaryUpdateOperator(bpy.types.Operator) :
  bl_idname = "pg.boundaryupdate"
  bl_label = "Boundary"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      global boundary
      boundary.build()
      #v1 = Vector3dd(min[0], min[1], min[2])
      min = context.scene.boundary_property.min
      max = context.scene.boundary_property.max
      v1 = Vector3dd(min[0], min[1], min[2])
      v2 = Vector3dd(max[0], max[1], max[2])
      bb = Box3dd(v1, v2)
      boundary.boundary.bounding_box = bb
      boundary.boundary.send()
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
    layout.prop(context.scene.boundary_property, "min", text="Min")
    layout.prop(context.scene.boundary_property, "max", text="Max")
    layout.operator(BoundaryUpdateOperator.bl_idname, text="Update")

class BoundaryProperty(bpy.types.PropertyGroup) :
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
  BoundaryProperty,
  BoundaryUpdateOperator,
  BoundaryPanel,
]

class BoundaryUI :
  def register():
    for c in classes:
      bpy.utils.register_class(c)
    bpy.types.Scene.boundary_property = bpy.props.PointerProperty(type=BoundaryProperty)

  def unregister() :
    del bpy.types.Scene.boundary_property
    for c in classes:
      bpy.utils.unregister_class(c)
