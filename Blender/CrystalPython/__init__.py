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

from bpy_extras.io_utils import (
    ImportHelper,
    ExportHelper,
)

# 読み込み元のディレクトリパスを取得
addon_dirpath = os.path.dirname(__file__)
# 読み込み元のディレクトリパスをシステムパスに追加
sys.path += [addon_dirpath]


class BLParticleSystem :
  def __init__(self):
    self.ps = ParticleSystemScene(scene)

  def convert_to_polygon_mesh(self, ob_name):
      # Create new mesh and a new object
      me = bpy.data.meshes.new(name = ob_name + "Mesh")
      ob = bpy.data.objects.new(ob_name, me)

      positions = self.ps.get_positions()
      coords = []
      for p in positions.values :
        coords.append( (p.x, p.y, p.z))
      # Make a mesh from a list of vertices/edges/faces
      me.from_pydata(coords, [], [])

      # Display name and update the mesh
      ob.show_name = True
      me.update()
      bpy.context.collection.objects.link(ob)

class BLTriangleMesh :
  def __init__(self):
    self.mesh = TriangleMeshScene(scene)

  def convert_to_polygon_mesh(self, name) :
    mesh = bpy.data.meshes.new(name = name)
    obj = bpy.data.objects.new(name, mesh)

    coords = []
    faces = []
    next_vertex = 0
    triangles = self.mesh.get_triangles()
    for t in triangles.values :
      coords.append( (t.v0.x, t.v0.y, t.v0.z ))
      coords.append( (t.v1.x, t.v1.y, t.v1.z ))
      coords.append( (t.v2.x, t.v2.y, t.v2.z ))
      faces.append( (next_vertex,next_vertex+1,next_vertex+2) )
      next_vertex += 3

    mesh.from_pydata(coords, [], faces)
    
    # Display name and update the mesh
    obj.show_name = True
    mesh.update()
    bpy.context.collection.objects.link(obj)

#      triangle.

#    self.mesh.
#    mesh.from_pydata()

  def convert_from_polygon_mesh(self, mesh) :
    #meshes = bpy.data.meshes

    positions = []
    print("num of vertices:", len(mesh.vertices))
    for vt in mesh.vertices:
      print("vertex index:{0:2} co:{1} normal:{2}".format(vt.index, vt.co, vt.normal))
      p = Vector3dd(vt.co[0], vt.co[1], vt.co[2])
      positions.append(p)

    #self.mesh.create_polygon_mesh_scene("", positions, normals, [], 0)
    triangles = Triangle3ddVector()
    for pl in mesh.polygons:
      print("polygon index:{0:2} ".format(pl.index), end="")
      print("vertices:", end="")
      for vi in pl.vertices:
        print("{0:2}, ".format(vi), end="")
      v0 = positions[pl.vertices[0]]
      v1 = positions[pl.vertices[1]]
      v2 = positions[pl.vertices[2]]
      v3 = positions[pl.vertices[3]]
      triangle1 = Triangle3dd(v0, v1, v2)
      triangles.add(triangle1)
      triangle2 = Triangle3dd(v0, v2, v3)
      triangles.add(triangle2)
      print("")
    self.mesh.create(triangles, "")

class BLVoxel:
  def __init__(self):
    self.voxel = VoxelScene(scene)

  def build(self):
    self.voxel.create_empty_voxel("name")

  def convert_to_polygon_mesh(self, ob_name):
      # Create new mesh and a new object
      me = bpy.data.meshes.new(name = ob_name)
      ob = bpy.data.objects.new(ob_name, me)

      grid = self.voxel.get_values()
      bb = grid.bb

      coords = []
      index = 0
      for x in range(0, grid.res[0]):
        for y in range(0, grid.res[1]):
          for z in range(0, grid.res[2]):
            b = grid.values[index]
            if b :
              coords.append( (x * 0.1, y * 0.1, z * 0.1) )
            index+=1
          
      # Make a mesh from a list of vertices/edges/faces
      me.from_pydata(coords, [], [])

      # Display name and update the mesh
      ob.show_name = True
      me.update()
      bpy.context.collection.objects.link(ob)


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
      pc = BLParticleSystem()
      positions = Vector3ddVector()
      positions.add(Vector3dd(0.0, 0.0, 0.0))
      pc.ps.create_empty("")
      pc.ps.set_positions(positions)
      pc.convert_to_polygon_mesh("")      
      return {'FINISHED'}

class MeshToPS(bpy.types.Operator) :
  bl_idname = "pg.meshtops"
  bl_label = "MeshToPS"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      selected_mesh = self.get_selected_mesh(context)
      mesh = BLTriangleMesh()
      mesh.convert_from_polygon_mesh(selected_mesh)
      mesh.convert_to_polygon_mesh("hello")
      voxel = BLVoxel()
      voxel.build()
      voxelizer = Voxelizer(scene)
      voxelizer.voxelize(mesh.mesh.id, voxel.voxel.id, 0.2)
      values = voxel.voxel.get_values()
      voxel.convert_to_polygon_mesh("voxel")
      ps = BLParticleSystem()
      ps.ps.create_empty("")
      voxel.voxel.convert_to_ps(ps.ps.id)
      ps.convert_to_polygon_mesh("ps")
      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

class PSToMesh(bpy.types.Operator) :
  bl_idname = "pg.pstomesh"
  bl_label = "PSToMesh"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      ps = BLParticleSystem()
      ps.ps.create_empty("")
      positions = Vector3ddVector()
      for i in range(0,10) :
        for j in range(0,10) :
          for k in range(0,10) :
            p = Vector3dd(i,j,k)
            positions.add(p)
      ps.ps.set_positions(positions)
      ps.convert_to_polygon_mesh("ps")

      mesh = BLTriangleMesh()
      mesh.mesh.create_empty("")

      builder = SurfaceBuilder(scene)
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
    layout.operator(MeshToPS.bl_idname, text="MeshToPS")
    layout.operator(PSToMesh.bl_idname, text="PSToMesh")
    layout.operator(ParticleSystemGenerator.bl_idname, text="PSGenerator")
    layout.operator(ParticleSystemImportOperator.bl_idname, text="PSImport")
    layout.operator(ParticleSystemExportOperator.bl_idname, text="PSExport")


classes = [
  FastParticlesPanel,
  MeshToPS,
  PSToMesh,
  ParticleSystemImportOperator,
  ParticleSystemExportOperator,
  ParticleSystemGenerator,
  SAMPLE31_OT_RotateObjectByMouseDragging,
  SAMPLE31_PT_RotateObjectByMouseDragging,
]

world = None
scene = None

def register():
  global world
  global scene
  world = World()
  scene = Scene(world)

  for c in classes:
    bpy.utils.register_class(c)

  #bpy.types.Scene.tutorial_comment = StringProperty(default = "")

def unregister():
  for c in classes:
    bpy.utils.unregister_class(c)

  #del bpy.types.Scene.tutorial_comment

if __name__ == "__main__":
  register()
