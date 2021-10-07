from physics.physics_labels import *
from scene.scene import Scene
from CrystalPLI import *

class SurfaceBuilder :
    def __init__(self, scene) :
        self.scene = scene

    def build_anisotorpic(self, particle_system_id, triangle_mesh_id, cell_length, effect_length) :
        create_physics_command(SPHSurfaceConstructionCommand.CommandNameLabel)
        set_arg_int(SPHSurfaceConstructionCommand.ParticleSystemIdLabel, particle_system_id)
        set_arg_int(SPHSurfaceConstructionCommand.TriangleMeshIdLabel, triangle_mesh_id)
        set_arg_float(SPHSurfaceConstructionCommand.CellLengthLabel, cell_length)
        set_arg_float(SPHSurfaceConstructionCommand.EffectLengthLabel, effect_length)
        is_ok = execute_command(self.scene.world)
        return is_ok
