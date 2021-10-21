import bpy
import CrystalPLI

from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from ui.bl_voxel import BLVoxel
from space.voxel_scene import Voxelizer

from ui.model import Model as model

class VoxelizerOperator(bpy.types.Operator) :
  bl_idname = "pg.voxelizeroperator"
  bl_label = "MeshToPS"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      selected_mesh = self.get_selected_mesh(context)
      mesh = BLTriangleMesh(model.scene)
      mesh.convert_from_polygon_mesh(selected_mesh)
      mesh.convert_to_polygon_mesh("hello")
      voxel = BLVoxel(model.scene)
      voxel.build()
      voxelizer = Voxelizer(model.scene)
      voxelizer.voxelize(mesh.mesh.id, voxel.voxel.id, 0.2)
      values = voxel.voxel.get_values()
      voxel.convert_to_polygon_mesh("voxel")
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

class VoxelizerPanel(bpy.types.Panel) :
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Voxelizer"
  
  def draw(self, context):
    layout = self.layout
    layout.operator(VoxelizerOperator.bl_idname, text="Voxelizer")
 