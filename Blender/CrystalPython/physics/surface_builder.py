from physics.physics_labels import *
from scene.scene import Scene
from CrystalPLI import *

class SurfaceBuilder :
    def __init__(self, scene) :
        self.scene = scene
    
    def build_isotorpic(self, particle_system_id, triangle_mesh_id, particle_radius, threshold) :
        create_physics_command(SPHSurfaceConstructionCommand.CommandNameLabel)
        set_arg_int(SPHSurfaceConstructionCommand.ParticleSystemIdLabel, particle_system_id)
        set_arg_int(SPHSurfaceConstructionCommand.TriangleMeshIdLabel, triangle_mesh_id)
        set_arg_float(SPHSurfaceConstructionCommand.ParticleRadiusLabel, particle_radius)
        set_arg_float(SPHSurfaceConstructionCommand.ThresholdLabel, threshold)
        set_arg_bool(SPHSurfaceConstructionCommand.IsIsotropicLabel, True)
        is_ok = execute_command(self.scene.world)
        return is_ok

    def build_anisotorpic(self, particle_system_id, triangle_mesh_id, particle_radius, threshold) :
        create_physics_command(SPHSurfaceConstructionCommand.CommandNameLabel)
        set_arg_int(SPHSurfaceConstructionCommand.ParticleSystemIdLabel, particle_system_id)
        set_arg_int(SPHSurfaceConstructionCommand.TriangleMeshIdLabel, triangle_mesh_id)
        set_arg_float(SPHSurfaceConstructionCommand.ParticleRadiusLabel, particle_radius)
        set_arg_float(SPHSurfaceConstructionCommand.ThresholdLabel, threshold)
        set_arg_bool(SPHSurfaceConstructionCommand.IsIsotropicLabel, False)
        is_ok = execute_command(self.scene.world)
        return is_ok
