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
import physics_command
import particle_system_scene
from polygon_mesh_scene import *
from triangle_mesh_scene import *
from voxel_scene import *
from physics_command import *
from scene import *
from bpy.props import *

from bpy_extras.io_utils import (
    ImportHelper,
    ExportHelper,
)

# 読み込み元のディレクトリパスを取得
addon_dirpath = os.path.dirname(__file__)
# 読み込み元のディレクトリパスをシステムパスに追加
sys.path += [addon_dirpath]


class BLPointCloud :    
  def convert_to_polygon_mesh(self, ob_name, coords):
      # Create new mesh and a new object
      me = bpy.data.meshes.new(name = ob_name + "Mesh")
      ob = bpy.data.objects.new(ob_name, me)

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
      pc = BLPointCloud()
      pc.convert_to_polygon_mesh("point-cloud", [(0.0, 0.0, 0.0)])      
      return {'FINISHED'}

class MeshToPS(bpy.types.Operator) :
  bl_idname = "pg.meshtops"
  bl_label = "MeshToPS"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      #pc = BLPointCloud("point-cloud", [(0.0, 0.0, 0.0)])      
      selected_mesh = self.get_selected_mesh(context)
      mesh = BLTriangleMesh()
      mesh.convert_from_polygon_mesh(selected_mesh)
      mesh.convert_to_polygon_mesh("hello")
      voxel = BLVoxel()
      voxel.build()
      voxelizer = Voxelizer(scene)
      voxelizer.voxelize(mesh.mesh.id, voxel.voxel.id, 0.2)
      values = voxel.voxel.get_values()
      return {'FINISHED'}

  def get_selected_mesh(self, context) :
    for o in bpy.data.objects:
      if o.type == 'MESH' and o.select_get():
        return o.to_mesh()
    return None

class TUTORIAL_OT_SayComment(bpy.types.Operator):
  bl_idname = "tutorial.saycomment"
  bl_label = "Say Comment"
  bl_options = {"REGISTER", "UNDO"}

  comment: StringProperty(default="Hello", options={'HIDDEN'})

  def execute(self, context):
      f = FluidScene(scene)
      f.create()
      self.report({'INFO'}, str(f.id))
      self.report({'INFO'}, addon_dirpath)
      self.report({'INFO'}, self.comment)
      return {'FINISHED'}

class ParticleFluidsPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "Tutorial"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
#    layout.prop(context.scene, "tutorial_comment")

    op_prop = layout.operator(TUTORIAL_OT_SayComment.bl_idname, text="Say")
    #op_prop.comment = context.scene.tutorial_comment

class FastParticlesPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "FastParticles"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
    layout.operator(MeshToPS.bl_idname, text="MeshToPS")
    layout.operator(ParticleSystemGenerator.bl_idname, text="PSGenerator")
    layout.operator(ParticleSystemImportOperator.bl_idname, text="PSImport")
    layout.operator(ParticleSystemExportOperator.bl_idname, text="PSExport")

classes = [
  ParticleFluidsPanel,
  TUTORIAL_OT_SayComment,
  FastParticlesPanel,
  MeshToPS,
  ParticleSystemImportOperator,
  ParticleSystemExportOperator,
  ParticleSystemGenerator,
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
