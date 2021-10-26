import bpy
from bpy_extras.io_utils import ImportHelper

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

class ParticleSystemImportPanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "PanelTitle"

  def draw(self, context):
    layout = self.layout
    layout.operator(ParticleSystemImportOperator.bl_idname, text="PSImport")

classes = [
  ParticleSystemImportOperator,
  ParticleSystemImportPanel,
]

class ParticleSystemImportUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
