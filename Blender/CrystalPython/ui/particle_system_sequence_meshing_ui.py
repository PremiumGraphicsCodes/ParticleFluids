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
        for i in range(1,10) :
            time_step = i
            file_path = os.path.join("tmp_txt", "test" + str(time_step) + ".txt")

            ps = ParticleSystemScene(model.scene)
            ps.create_empty("")
            FileIO.import_txt(model.scene, ps.id, file_path)
            
            mesh = TriangleMeshScene(model.scene)
            mesh.create_empty("")
            
            builder = SurfaceBuilder(model.scene)
            builder.build_anisotorpic(ps.id, mesh.id, 1.0, 2.0)

#            FileIO.ex
            #mesh.convert_to_polygon_mesh("")
            model.scene.delete(ps.id, False)
            model.scene.delete(mesh.id, False)
        return {'FINISHED'}
    

class ParticleSystemSequenceMeshingPanel(bpy.types.Panel):
    bl_label = "Start"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Animation"
    bl_context = "objectmode"

    def draw(self, context):
        self.layout.operator(ParticleSystemSequenceMeshingOperator.bl_idname, text="PSSeqMesher")

classes = [
    ParticleSystemSequenceMeshingOperator,
    ParticleSystemSequenceMeshingPanel,
]

class ParticleSystemSequenceMeshingUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)