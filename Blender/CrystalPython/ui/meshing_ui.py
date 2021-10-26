import bpy
from CrystalPLI import Vector3dd
from CrystalPLI import Vector3ddVector

from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from physics.surface_builder import SurfaceBuilder

from ui.model import Model as model

class MeshingOperator(bpy.types.Operator) :
  bl_idname = "pg.meshing"
  bl_label = "Meshing"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      ps = BLParticleSystem(model.scene)
      ps.ps.create_empty("")
      positions = Vector3ddVector()
      for i in range(0,10) :
        for j in range(0,10) :
          for k in range(0,10) :
            p = Vector3dd(i,j,k)
            positions.add(p)
      ps.ps.set_positions(positions)
      ps.convert_to_polygon_mesh("ps")

      mesh = BLTriangleMesh(model.scene)
      mesh.mesh.create_empty("")

      builder = SurfaceBuilder(model.scene)
      builder.build_anisotorpic(ps.ps.id, mesh.mesh.id, 1.0, 2.0)
      mesh.convert_to_polygon_mesh("")
      return {'FINISHED'}

class MeshingPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "Meshing"

  def draw(self, context):
    layout = self.layout
#    layout.operator(VoxelizerOperator.bl_idname, text="Voxelizer")
    layout.operator(MeshingOperator.bl_idname, text="Meshing")

classes = [
  MeshingOperator,
  MeshingPanel,
]

class MeshingUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)