import bpy
from CrystalPLI import Vector3dd
from CrystalPLI import Vector3ddVector

from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from physics.surface_builder import SurfaceBuilder

from ui.model import Model as model

class PSToMeshOperator(bpy.types.Operator) :
  bl_idname = "pg.pstomesh"
  bl_label = "PSToMesh"
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
