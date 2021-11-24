import bpy
from ui.model import Model as model
from ui.bl_particle_system import BLParticleSystem
from CrystalPLI import Vector3dd, Vector3ddVector
from scene.file_io import FileIO
import os

class ParticleSystemSequenceImporter :
    def __init__(self) :
        self.ps = None
        self.__running = False

    def build(self):
        if self.ps == None :
            self.ps = BLParticleSystem(model.scene)
            self.ps.ps.create_empty("")
            self.ps.convert_to_polygon_mesh("")               

    def start(self):
        self.__running = True

    def stop(self):
        self.__running = False

    def step(self, frame):
        file_path = os.path.join("tmp_txt", "test" + str(frame) + ".txt")
        FileIO.import_txt(model.scene, self.ps.ps.id, file_path)
        self.ps.update()

    def is_running(self):
        return self.__running

animator = ParticleSystemSequenceImporter()

def on_frame_changed_ps_seq_importer(scene):
    if animator.ps == None :
        return

    if animator.is_running() :
        animator.step(scene.frame_current)

class ParticleSystemSequenceImportOperator(bpy.types.Operator):
    bl_idname = "pg.particlesystemsequenceimportoperator"
    bl_label = "ParticleSystem"
    bl_description = "Hello"

    def execute(self, context) :
        if animator.ps == None :
            animator.build()

        if not animator.is_running() :
            animator.start()
        else :
            animator.stop()
        return {'FINISHED'}

class ParticleSystemSequenceImportPanel(bpy.types.Panel):
    bl_label = "PSSeqImport"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "PFTools"
    bl_context = "objectmode"

    def draw(self, context):
        op = ParticleSystemSequenceImportOperator
        if not animator.is_running():
            self.layout.operator(op.bl_idname,text="Start", icon='PLAY')
        else:
            self.layout.operator(op.bl_idname,text="Stop", icon='PAUSE')

classes = [
  ParticleSystemSequenceImportOperator,
  ParticleSystemSequenceImportPanel,
]

class ParticleSystemSequenceImportUI :
    def register():
        for c in classes:
            bpy.utils.register_class(c)
        #animator.init()
        bpy.app.handlers.frame_change_pre.append(on_frame_changed_ps_seq_importer)

    def unregister():
        for c in classes:
            bpy.utils.unregister_class(c)