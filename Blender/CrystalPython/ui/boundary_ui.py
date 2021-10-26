import bpy
from bpy.props import FloatProperty, FloatVectorProperty

from physics.fluid_scene import FluidScene
from ui.bl_boundary import BLBoundary

from ui.model import Model as model
from CrystalPLI import Vector3dd, Box3dd

boundary = BLBoundary(model.scene)
min = [0,0,0]
max = [1,1,1]

class BoundaryUpdateOperator(bpy.types.Operator) :
  bl_idname = "pg.boundaryupdate"
  bl_label = "Boundary"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      global boundary
      boundary.build()
      v1 = Vector3dd(min[0], min[1], min[2])
      v2 = Vector3dd(max[0], max[1], max[2])
      bb = Box3dd(v1, v2)
      boundary.boundary.bounding_box = bb
      boundary.boundary.send()
      return {'FINISHED'}

def set_min(self, value) :
    global min
    min = value

def get_min(self) :
    global min
    return min

def set_max(self, value) :
    global max
    max = value

def get_max(self) :
    global max
    return max

def init_props():
    scene = bpy.types.Scene
    scene.min_prop = FloatVectorProperty(
        name="min",
        description="Min",
        default=(0.0, 0.0, 0.0),
        set=set_min,
        get=get_min,
    )
    scene.max_prop = FloatVectorProperty(
        name="max",
        description="Max",
        default=(1.0, 1.0, 1.0),
        set=set_min,
        get=get_min,
    )

def clear_props():
    scene = bpy.types.Scene
    del scene.min_prop
    del scene.max_prop

class BoundaryPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Boundary"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene, "min_prop", text="Min")
    layout.prop(context.scene, "max_prop", text="Max")
    layout.operator(BoundaryUpdateOperator.bl_idname, text="Update")

classes = [
  BoundaryUpdateOperator,
  BoundaryPanel,
]

class BoundaryUI :
  def register():
    init_props()
    for c in classes:
      bpy.utils.register_class(c)

  def unregister() :
    clear_props()
    for c in classes:
      bpy.utils.unregister_class(c)
 