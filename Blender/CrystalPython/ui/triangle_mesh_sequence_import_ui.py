import bpy
from bpy.props import (StringProperty,
                       PointerProperty,
                       )

from bpy.types import (Panel,
                       Operator,
                       AddonPreferences,
                       PropertyGroup,
                       )
from ui.model import Model as model
from ui.bl_triangle_mesh import BLTriangleMesh
from CrystalPLI import Vector3dd, Vector3ddVector
from scene.file_io import FileIO
import os

class TriangleMeshSequenceImporter :
    def __init__(self) :
        self.tm = None
        self.__running = False

    def init(self):
        if self.tm == None :
            self.tm = BLTriangleMesh(model.scene)
            self.tm.mesh.create_empty("")
            self.tm.convert_to_polygon_mesh("")               

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self):
        time_step = bpy.context.scene.frame_current
        file_path = os.path.join("tmp_stl", "test" + str(time_step) + ".stl")

        self.tm.mesh.import_stl(file_path)
        triangles = self.tm.mesh.get_triangles()
        self.tm.update()

    def is_running(self):
        return self.__running

animator = TriangleMeshSequenceImporter()

class TriangleMeshSequenceImportOperator(bpy.types.Operator):
    bl_idname = "pg.trianglemeshsequenceimportoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"

    def modal(self, context, event):
        active_obj = context.active_object

        if animator.is_running() :
            animator.step()

        # エリアを再描画
        if context.area:
            context.area.tag_redraw()

        return {'PASS_THROUGH'}

    def invoke(self, context, event):
        if context.area.type == 'VIEW_3D':
            # [開始] ボタンが押された時の処理
            if not animator.is_running():
                # モーダルモードを開始
                context.window_manager.modal_handler_add(self)
                animator.init()
                animator.start()

                print("animation start")
                return {'RUNNING_MODAL'}
            # [終了] ボタンが押された時の処理
            else:
                animator.stop()
                print("animation stop")
                return {'FINISHED'}
        else:
            return {'CANCELLED'}


class TriangleMeshSequenceImportPanel(bpy.types.Panel):
    bl_label = "TMSeqImport"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "PFTools"
    bl_context = "objectmode"

    def draw(self, context):
        op = TriangleMeshSequenceImportOperator
        if not animator.is_running():
            self.layout.operator(op.bl_idname,text="ImportStart", icon='PLAY')
        else:
            self.layout.operator(op.bl_idname,text="ImportStop", icon='PAUSE')

classes = [
  TriangleMeshSequenceImportOperator,
  TriangleMeshSequenceImportPanel,
]

class TriangleMeshSequenceImportUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)



# ------------------------------------------------------------------------
#    Scene Properties
# ------------------------------------------------------------------------

class MyProperties(PropertyGroup):

    path : StringProperty(
        name="",
        description="Path to Directory",
        default="",
        maxlen=1024,
        subtype='DIR_PATH')

# ------------------------------------------------------------------------
#    Panel in Object Mode
# ------------------------------------------------------------------------

class OBJECT_PT_CustomPanel(Panel):
    bl_idname = "OBJECT_PT_my_panel"
    bl_label = "My Panel"
    bl_space_type = "VIEW_3D"   
    bl_region_type = "UI"
    bl_category = "Tools"
    bl_context = "objectmode"

    def draw(self, context):
        layout = self.layout
        scn = context.scene
        col = layout.column(align=True)
        col.prop(scn.my_tool, "path", text="")

        # print the path to the console
        print (scn.my_tool.path)

# ------------------------------------------------------------------------
#    Registration
# ------------------------------------------------------------------------

test_classes = (
    MyProperties,
    OBJECT_PT_CustomPanel
)

class Dir_Select_Sample_UI :
    def register():
        for cls in test_classes:
            bpy.utils.register_class(cls)
        bpy.types.Scene.my_tool = PointerProperty(type=MyProperties)
    
    def unregister():
        for cls in reversed(test_classes):
            bpy.utils.unregister_class(cls)
        del bpy.types.Scene.my_tool
