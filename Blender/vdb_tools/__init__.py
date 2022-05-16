import bpy

from .filter import VDB_TOOLS_Filter_UI
from .resampling import VDB_TOOLS_Resampling_UI
from .composite import VDB_TOOLS_Composite_UI

bl_info = {
    "name": "VDBToolsForBlender",
    "author": "ぬっち（Nutti）",
    "version": (0, 1),
    "blender": (2, 80, 0),
    "location": "",
    "description": "",
    "warning": "",
    "support": "TESTING",
    "doc_url": "",
    "tracker_url": "",
    "category": "Object"
}

def register():
    VDB_TOOLS_Filter_UI.register()
    VDB_TOOLS_Resampling_UI.register()
    VDB_TOOLS_Composite_UI.register()

def unregister():
    VDB_TOOLS_Composite_UI.unregister()
    VDB_TOOLS_Resampling_UI.unregister()
    VDB_TOOLS_Filter_UI.unregister()

if __name__ == "__main__":
    register()