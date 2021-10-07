import physics_labels
from scene import Scene
from CrystalPLI import *

class FluidScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = 0
        self.source_particle_system_id = 0
        self.particle_radius = 1.0
        self.density = 1.0
        self.stiffness = 1.0
        self.viscosity = 1.0
        self.is_boundary = False;
        self.name = ""

    def create(self) :
        create_physics_command(physics_labels.FluidSceneCreateCommand.CommandNameLabel)
        execute_command(self.scene.world)
        self.id = get_result_int(physics_labels.FluidSceneCreateCommand.NewIdLabel)

    def send(self) :
        create_physics_command(physics_labels.FluidSceneUpdateCommand.CommandNameLabel)
        set_arg_int(physics_labels.FluidSceneUpdateCommand.IdLabel, self.id)
        set_arg_int(physics_labels.FluidSceneUpdateCommand.ParticleSystemIdLabel, self.source_particle_system_id)
        set_arg_float(physics_labels.FluidSceneUpdateCommand.ParticleRadiusLabel, self.particle_radius)
        set_arg_float(physics_labels.FluidSceneUpdateCommand.DensityLabel, self.density)
        set_arg_float(physics_labels.FluidSceneUpdateCommand.StiffnessLabel, self.stiffness)
        set_arg_float(physics_labels.FluidSceneUpdateCommand.ViscosityLabel, self.viscosity)
        set_arg_bool(physics_labels.FluidSceneUpdateCommand.IsBoundary, self.is_boundary)
        set_arg_string(physics_labels.FluidSceneUpdateCommand.NameLabel, self.name)
        is_ok = execute_command(self.scene.world)
        return is_ok