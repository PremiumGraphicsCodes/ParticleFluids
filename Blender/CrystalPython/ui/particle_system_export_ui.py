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

class ParticleSystemExportPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "PSExport"

  def draw(self, context):
    layout = self.layout
    layout.operator(ParticleSystemExportOperator.bl_idname, text="PSExport")

classes = [
  ParticleSystemExportOperator,
  ParticleSystemExportPanel,
]

class ParticleSystemExportUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
