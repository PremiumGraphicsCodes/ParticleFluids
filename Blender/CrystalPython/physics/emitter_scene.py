from physics.physics_labels import EmitterSceneCreateCommand, EmitterSceneUpdateCommand
from scene.scene import Scene
from CrystalPLI import *

class FluidScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = 0
        self.source_particle_system_id = 0
        self.particle_radius = 1.0
        self.density = 1.0
        self.stiffness = 0.25
        self.viscosity = 10.0

    def create(self) :
        create_physics_command(EmitterSceneCreateCommand.CommandNameLabel)
        execute_command(self.scene.world)
        self.id = get_result_int(EmitterSceneCreateCommand.NewIdLabel)

    def send(self) :
        create_physics_command(EmitterSceneUpdateCommand.CommandNameLabel)
        set_arg_int(EmitterSceneUpdateCommand.IdLabel, self.id)
        set_arg_int(EmitterSceneUpdateCommand.ParticleSystemIdLabel, self.source_particle_system_id)
        set_arg_float(EmitterSceneUpdateCommand.ParticleRadiusLabel, self.particle_radius)
        set_arg_float(EmitterSceneUpdateCommand.DensityLabel, self.density)
        set_arg_float(EmitterSceneUpdateCommand.StiffnessLabel, self.stiffness)
        set_arg_float(EmitterSceneUpdateCommand.ViscosityLabel, self.viscosity)
        #set_arg_bool(FluidSceneUpdateCommand.IsBoundary, self.is_boundary)
        #set_arg_string(FluidSceneUpdateCommand.NameLabel, self.name)
        is_ok = execute_command(self.scene.world)
        return is_ok

   #CommandNameLabel="EmitterSceneUpdateCommand"
   #IdLabel="Id"
   #ParticleSystemIdLabel="ParticleSystemId"
   #ParticleRadiusLabel="ParticleRadius"
   #StiffnessLabel="Stiffness"
   #ViscosityLabel="Viscosity"
   #InitialVelocityLabel="InitialVelocity"
   #DensityLabel="Density"
   #NameLabel="Name"
   #StartStepLabel="StartStep"
   #EndStepLabel="EndStep"
   #IntervalLabel="Interval"

    #def get_positions(self) :
    #    create_scene_command(ParticleSystemGetCommand.CommandNameLabel)
    #    set_arg_int(ParticleSystemGetCommand.PSIdLabel, self.id)
    #    is_ok = execute_command(self.scene.world)
    #    return get_result_vector3dd_vector(ParticleSystemGetCommand.PositionsLabel)

