bl_info = {
    "name": "ParticleFluids",
    "author": "ぬっち（Nutti）",
    "version": (3, 0),
    "blender": (2, 80, 0),
    "location": "",
    "description": "アドオンの有効化と無効化を試すためのサンプル",
    "warning": "",
    "support": "TESTING",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Object"
}
# bpyインポート
import bpy
# osインポート(ディレクトリ取得のため)
import os
# sysインポート(システムパス追加のため)
import sys

# 読み込み元のディレクトリパスを取得
addon_dirpath = os.path.dirname(__file__)
# 読み込み元のディレクトリパスをシステムパスに追加
sys.path += [addon_dirpath]
import bpy
import CrystalPLI
import scene
import physics_command
from physics_command import *
from scene import *
from bpy.props import *

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

class TUTORIAL_PT_SamplePanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "Tutorial"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
    layout.prop(context.scene, "tutorial_comment")

    op_prop = layout.operator(TUTORIAL_OT_SayComment.bl_idname, text="Say")
    op_prop.comment = context.scene.tutorial_comment

    layout.operator(MeshToPS.bl_idname, text="MeshToPS")
#    op_prop.comment = context.scene.tutorial_comment


classes = [
  TUTORIAL_PT_SamplePanel,
  TUTORIAL_OT_SayComment,
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