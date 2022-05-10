import bpy

from .filter import VDB_TOOLS_Filter_UI
from .composite import VDB_TOOLS_Composite_UI

# アドオンに関する情報を保持する、bl_info変数
bl_info = {
    "name": "サンプル 2-1: オブジェクトを生成するアドオン",
    "author": "ぬっち（Nutti）",
    "version": (3, 0),
    "blender": (2, 80, 0),
    "location": "3Dビューポート > 追加 > メッシュ",
    "description": "オブジェクトを生成するサンプルアドオン",
    "warning": "",
    "support": "TESTING",
    "doc_url": "",
    "tracker_url": "",
    "category": "Object"
}

def register():
    VDB_TOOLS_Filter_UI.register()
    VDB_TOOLS_Composite_UI.register()

def unregister():
    VDB_TOOLS_Composite_UI.unregister()
    VDB_TOOLS_Filter_UI.unregister()


# メイン処理
if __name__ == "__main__":
    register()