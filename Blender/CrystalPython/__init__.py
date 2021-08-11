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
import sys

addon_dirpath = os.path.dirname(__file__)
sys.path += [addon_dirpath]

import bpy
import CrystalPLI
import scene
import physics_command
from physics_command import *
from scene import *
from bpy.props import *



# 読み込み元のディレクトリパスを取得
addon_dirpath = os.path.dirname(__file__)
# 読み込み元のディレクトリパスをシステムパスに追加
sys.path += [addon_dirpath]

def fluid_point_cloud(ob_name, coords, edges=[], faces=[]):
    """Create point cloud object based on given coordinates and name.

    Keyword arguments:
    ob_name -- new object name
    coords -- float triplets eg: [(-1.0, 1.0, 0.0), (-1.0, -1.0, 0.0)]
    """

    # Create new mesh and a new object
    me = bpy.data.meshes.new(name = ob_name + "Mesh")
    ob = bpy.data.objects.new(ob_name, me)

    # Make a mesh from a list of vertices/edges/faces
    me.from_pydata(coords, edges, faces)

    # Display name and update the mesh
    ob.show_name = True
    me.update()
    return ob

class MeshToPS(bpy.types.Operator) :
  bl_idname = "pg.meshtops"
  bl_label = "MeshToPS"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      pc = fluid_point_cloud("point-cloud", [(0.0, 0.0, 0.0)])
      bpy.context.collection.objects.link(pc)
      return {'FINISHED'}

class TUTORIAL_OT_SayComment(bpy.types.Operator):
  bl_idname = "tutorial.saycomment"
  bl_label = "Say Comment"
  bl_options = {"REGISTER", "UNDO"}

  comment: StringProperty(default="Hello", options={'HIDDEN'})

  def execute(self, context):
      w = World()
      s = Scene(w)
      f = FluidScene(s)
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
    layout.prop(context.scene, "tutorial_comment")

    op_prop = layout.operator(TUTORIAL_OT_SayComment.bl_idname, text="Say")
    op_prop.comment = context.scene.tutorial_comment

class FastParticlesPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "FastParticles"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
    layout.operator(MeshToPS.bl_idname, text="MeshToPS")


classes = [
  ParticleFluidsPanel,
  TUTORIAL_OT_SayComment,
  FastParticlesPanel,
  MeshToPS,
]

def register():
  for c in classes:
    bpy.utils.register_class(c)

  bpy.types.Scene.tutorial_comment = StringProperty(default = "")

def unregister():
  for c in classes:
    bpy.utils.unregister_class(c)

  del bpy.types.Scene.tutorial_comment

if __name__ == "__main__":
  register()
