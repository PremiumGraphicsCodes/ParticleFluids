import bpy
from CrystalPLI import Vector3dd
from CrystalPLI import Vector3ddVector

from bpy.props import (
    FloatProperty,
)

from physics.fluid_scene import FluidScene
from ui.bl_fluid import BLFluid

from ui.model import Model as model

particle_radius = 0.2

class FluidOperator(bpy.types.Operator) :
  bl_idname = "pg.fluidoperator"
  bl_label = "Fluid"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      selected_mesh = self.get_selected_mesh(context)
      
#      self.fluid.
      self.fluid = BLFluid(model.scene)
      global particle_radius
      self.fluid.fluid.particle_radius = particle_radius
#      self.fluid.fluid.
      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

  def convert_from_polygon_mesh(self, mesh) :
    positions = []
    print("num of vertices:", len(mesh.vertices))
    for vt in mesh.vertices:
      print("vertex index:{0:2} co:{1} normal:{2}".format(vt.index, vt.co, vt.normal))
      p = Vector3dd(vt.co[0], vt.co[1], vt.co[2])
      positions.append(p)
    return positions

def set_particle_radius(self, value) :
    global particle_radius
    particle_radius = value
    return None

def get_particle_radius(self):
  global particle_radius
  return particle_radius

def init_props():
    scene = bpy.types.Scene
#    scene.divide_length_prop = FloatProperty(
#        name="divide_length",
#        description="DivideLength",
#        default=0.2,
#        min=0.0,
#        max=100.0,
#        get=get_divide_length,
#        set=set_divide_length
#    )

def clear_props():
    scene = bpy.types.Scene
#   del scene.divide_length_prop

class FluidPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Fluid"
  
  def draw(self, context):
    layout = self.layout
#    layout.prop(context.scene, "divide_length_prop", text="DivideLength")
#    layout.operator(VoxelizerOperator.bl_idname, text="Voxelizer")

classes = [
  FluidOperator,
  FluidPanel,
]

class FluidUI :
  def register():
    init_props()
    for c in classes:
      bpy.utils.register_class(c)

  def unregister() :
    clear_props()
    for c in classes:
      bpy.utils.unregister_class(c)
 