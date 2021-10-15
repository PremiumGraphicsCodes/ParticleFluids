from physics.physics_labels import *
from physics.csg_boundary_scene import CSGBoundaryScene
from scene.scene import Scene
from CrystalPLI import *

class SolverScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1
        self.time_step = 0.03
        self.effect_length = 2.25
        self.fluids = []
        self.boundaries = []
        self.external_force = Vector3df(0.0, 0.0, -9.8)

    def create(self) :
        create_physics_command(PhysicsSolverCreateCommand.CommandNameLabel)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(PhysicsSolverCreateCommand.NewIdLabel)
        return is_ok

    def send(self) :
        create_physics_command(PhysicsSolverUpdateCommand.CommandNameLabel)
        set_arg_int(PhysicsSolverUpdateCommand.IdLabel, self.id)
        fluid_ids = []
        for f in self.fluids :
            fluid_ids.append(f.id)
        boundary_ids = []
        for b in self.boundaries :
            boundary_ids.append(b.id)
        set_arg_int_vector(PhysicsSolverUpdateCommand.FluidSceneIdsLabel, fluid_ids)
        set_arg_int_vector(PhysicsSolverUpdateCommand.CSGBoundarySceneIdsLabel, boundary_ids)
        set_arg_vector3df(PhysicsSolverUpdateCommand.ExternalForceLabel, self.external_force)
        set_arg_float(PhysicsSolverUpdateCommand.TimeStepLabel, self.time_step)
        set_arg_float(PhysicsSolverUpdateCommand.EffectLengthLabel, self.effect_length)
        is_ok = execute_command(self.scene.world)
        return is_ok

    def simulate(self) :
        create_physics_command(FluidSimulationCommand.CommandNameLabel)
        set_arg_int(FluidSimulationCommand.SolverIdLabel, self.id)
        is_ok = execute_command(self.scene.world)
        return is_ok
