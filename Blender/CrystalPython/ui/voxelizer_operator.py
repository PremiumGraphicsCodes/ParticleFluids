import bpy
import CrystalPLI

from bpy.props import (
    FloatProperty,
)

from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from ui.bl_voxel import BLVoxel
from space.voxel_scene import Voxelizer

from ui.model import Model as model

divide_length = 0.2

class VoxelizerOperator(bpy.types.Operator) :
  bl_idname = "pg.voxelizeroperator"
  bl_label = "MeshToPS"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      selected_mesh = self.get_selected_mesh(context)
      mesh = BLTriangleMesh(model.scene)
      mesh.convert_from_polygon_mesh(selected_mesh)
      voxel = BLVoxel(model.scene)
      voxel.build()
      voxelizer = Voxelizer(model.scene)
#      scene = bpy.types.Scene
#      divide_length = float(scene.divide_length_prop) 
      global divide_length
      voxelizer.voxelize(mesh.mesh.id, voxel.voxel.id, divide_length)
      values = voxel.voxel.get_values()
      #voxel.convert_to_polygon_mesh("voxel")
      ps = BLParticleSystem(model.scene)
      ps.ps.create_empty("")
      voxel.voxel.convert_to_ps(ps.ps.id)
      ps.convert_to_polygon_mesh("ps")
      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

def set_divide_length(self, value) :
    global divide_length
    divide_length = value
    return None

def get_divide_length(self):
  global divide_length
  return divide_length

def init_props():
    scene = bpy.types.Scene
    scene.divide_length_prop = FloatProperty(
        name="divide_length",
        description="DivideLength",
        default=0.2,
        min=0.0,
        max=100.0,
        get=get_divide_length,
        set=set_divide_length
    )

def clear_props():
    scene = bpy.types.Scene
    del scene.divide_length_prop


class VoxelizerPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "PFTools"
  bl_label = "Voxelizer"
  
  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene, "divide_length_prop", text="DivideLength")
    layout.operator(VoxelizerOperator.bl_idname, text="Voxelizer")

classes = [
  VoxelizerOperator,
  VoxelizerPanel,
]

class VoxelizerUI :
  def register():
    init_props()
    for c in classes:
      bpy.utils.register_class(c)

  def unregister() :
    clear_props()
    for c in classes:
      bpy.utils.unregister_class(c)
 