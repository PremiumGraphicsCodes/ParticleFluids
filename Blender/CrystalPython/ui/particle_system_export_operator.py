import bpy
from bpy_extras.io_utils import ExportHelper

class ParticleSystemExportOperator(bpy.types.Operator, ExportHelper) :
  bl_idname = "pg.particlesystemexportoperator"
  bl_label = "ParticleSystemExport"
  bl_options = {"UNDO"}

  filename_ext = ".pcd"

  def execute(self, context) :
    return {"FINISHED"}

  def draw(self, context) :
    pass