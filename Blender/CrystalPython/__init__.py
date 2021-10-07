# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

bl_info = {
    "name" : "TestVSCode",
    "author" : "PremiumGraphics",
    "description" : "",
    "blender" : (2, 80, 0),
    "version" : (0, 0, 1),
    "location" : "",
    "warning" : "",
    "category" : "Generic"
}

import os
#from polygon_mesh_scene import PolygonMeshScene
import sys

addon_dirpath = os.path.dirname(__file__)
sys.path += [addon_dirpath]

import bpy
import CrystalPLI
import scene

from scene.particle_system_scene import *
from scene.polygon_mesh_scene import *
from scene.triangle_mesh_scene import *
from space.voxel_scene import *
from physics.fluid_scene import *
from physics.solver_scene import *
from physics.csg_boundary_scene import *
from physics.surface_builder import *
from scene import *
from bpy.props import *
from ui.animation_sample import *
from ui.bl_particle_system import *
from ui.bl_triangle_mesh import *
from ui.bl_voxel import *
from ui.model import Model as model
from ui.mesh_to_ps_operator import MeshToPSOperator

from bpy_extras.io_utils import (
    ImportHelper,
    ExportHelper,
)

# 読み込み元のディレクトリパスを取得
addon_dirpath = os.path.dirname(__file__)
# 読み込み元のディレクトリパスをシステムパスに追加
sys.path += [addon_dirpath]



class ParticleSystemImportOperator(bpy.types.Operator, ImportHelper) :
  bl_idname = "pg.particlesystemimportoperator"
  bl_label = "ParticleSystemImport"
  bl_options = {"UNDO"}

  def execute(self, context) :
#    ps = particle_system_scene()
#    ps.
    return {"FINISHED"}

  def draw(self, context) :
    pass

class ParticleSystemExportOperator(bpy.types.Operator, ExportHelper) :
  bl_idname = "pg.particlesystemexportoperator"
  bl_label = "ParticleSystemExport"
  bl_options = {"UNDO"}

  filename_ext = ".pcd"

  def execute(self, context) :
    return {"FINISHED"}

  def draw(self, context) :
    pass

class ParticleSystemGenerator(bpy.types.Operator) :
  bl_idname = "pg.particlesystemgenerator"
  bl_label = "ParticleSystemGenerator"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      pc = BLParticleSystem(model.scene)
      positions = Vector3ddVector()
      positions.add(Vector3dd(0.0, 0.0, 0.0))
      pc.ps.create_empty("")
      pc.ps.set_positions(positions)
      pc.convert_to_polygon_mesh("")      
      return {'FINISHED'}

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

class FastParticlesPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "FastParticles"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
    layout.operator(MeshToPSOperator.bl_idname, text="MeshToPS")
    layout.operator(PSToMeshOperator.bl_idname, text="PSToMesh")
    layout.operator(ParticleSystemGenerator.bl_idname, text="PSGenerator")
    layout.operator(ParticleSystemImportOperator.bl_idname, text="PSImport")
    layout.operator(ParticleSystemExportOperator.bl_idname, text="PSExport")


classes = [
  FastParticlesPanel,
  MeshToPSOperator,
  PSToMeshOperator,
  ParticleSystemImportOperator,
  ParticleSystemExportOperator,
  ParticleSystemGenerator,
  SAMPLE31_OT_RotateObjectByMouseDragging,
  SAMPLE31_PT_RotateObjectByMouseDragging,
]

def register():
  for c in classes:
    bpy.utils.register_class(c)

  #bpy.types.Scene.tutorial_comment = StringProperty(default = "")

def unregister():
  for c in classes:
    bpy.utils.unregister_class(c)

  #del bpy.types.Scene.tutorial_comment

if __name__ == "__main__":
  register()
