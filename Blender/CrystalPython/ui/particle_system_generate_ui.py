import bpy
from CrystalPLI import World, Vector3dd, Vector3ddVector
from scene.scene import Scene
from ui.bl_particle_system import BLParticleSystem
from ui.model import Model as model

class ParticleSystemGenerateOperator(bpy.types.Operator) :
  bl_idname = "pg.particlesystemgenerator"
  bl_label = "ParticleSystemGenerator"
  bl_options = {"REGISTER", "UNDO"}

  def execute(self, context) :
      pc = BLParticleSystem(model.scene)
      positions = Vector3ddVector()
      positions.add(Vector3dd(0.0, 0.0, 0.0))
      pc.ps.create_empty("")
      pc.ps.set_positions(positions)
      pc.convert_to_polygon_mesh("")      
      return {'FINISHED'}

class ParticleSystemGeneratePanel(bpy.types.Panel):
  bl_space_type = "VIEW_3D"
  bl_region_type = "UI"
  bl_category = "ParticleFluids"
  bl_label = "ParticleSystemGenerate"

  def draw(self, context):
    layout = self.layout
#    layout.operator(VoxelizerOperator.bl_idname, text="Voxelizer")
    layout.operator(ParticleSystemGenerateOperator.bl_idname, text="PSGenerator")

classes = [
  ParticleSystemGenerateOperator,
  ParticleSystemGeneratePanel,
]

class ParticleSystemGenerateUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)