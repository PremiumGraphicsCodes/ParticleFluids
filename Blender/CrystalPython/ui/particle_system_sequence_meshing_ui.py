import bpy
from ui.model import Model as model
from ui.bl_particle_system import BLParticleSystem
from ui.bl_triangle_mesh import BLTriangleMesh
from physics.surface_builder import SurfaceBuilder
from CrystalPLI import Vector3dd, Vector3ddVector
from scene.particle_system_scene import ParticleSystemScene
from scene.triangle_mesh_scene import TriangleMeshScene
from scene.file_io import FileIO
from scene.scene import *
import os

class ParticleSystemSequenceMeshingOperator(bpy.types.Operator) :
    bl_idname = "pg.particlesystemsequencemeshingoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"

    def execute(self, context) :
        prop = context.scene.meshing_property
        cell_length = prop.cell_length_prop
        effect_length = prop.effect_length_prop

        for i in range(1,10) :
            time_step = i
            file_path = os.path.join("tmp_txt", "test" + str(time_step) + ".txt")

            ps = ParticleSystemScene(model.scene)
            ps.create_empty("")
            FileIO.import_txt(model.scene, ps.id, file_path)
            
            mesh = TriangleMeshScene(model.scene)
            mesh.create_empty("")
            
            builder = SurfaceBuilder(model.scene)
            builder.build_anisotorpic(ps.id, mesh.id, cell_length, effect_length)

            export_file_path = os.path.join("tmp_stl", "test" + str(time_step) + ".stl")
            mesh.export_stl(export_file_path)

#            FileIO.ex
            #mesh.convert_to_polygon_mesh("")
            model.scene.delete(ps.id, False)
            model.scene.delete(mesh.id, False)
        return {'FINISHED'}

class MeshingProperty(bpy.types.PropertyGroup) :
  cell_length_prop : bpy.props.FloatProperty(
    name="cell_length",
    description="CellLength",
    default=1.0,
    min = 0.0,
    max = 100.0,
  )
  effect_length_prop : bpy.props.FloatProperty(
    name="effect_length",
    description="EffectLength",
    default=2.0,
    min=0.0,
    max=100.0,
  )

class ParticleSystemSequenceMeshingPanel(bpy.types.Panel):
    bl_label = "Start"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Animation"
    bl_context = "objectmode"

    def draw(self, context):
        prop = context.scene.meshing_property
        self.layout.prop(prop, "cell_length_prop", text="CellLength")
        self.layout.prop(prop, "effect_length_prop", text="EffectLength")
        self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname, text="PSSeqMesher")

classes = [
    ParticleSystemSequenceMeshingOperator,
    ParticleSystemSequenceMeshingPanel,
    MeshingProperty
]

class ParticleSystemSequenceMeshingUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        bpy.types.Scene.meshing_property = bpy.props.PointerProperty(type=MeshingProperty)


    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)
        del bpy.types.Scene.meshing_property