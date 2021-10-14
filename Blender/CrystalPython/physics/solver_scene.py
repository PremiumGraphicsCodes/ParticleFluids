from physics.physics_labels import *
from scene.scene import Scene
from CrystalPLI import *

class SolverScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1;

    def create(self) :
        create_physics_command(PhysicsSolverCreateCommand.CommandNameLabel)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(PhysicsSolverCreateCommand.NewIdLabel)
        return is_ok

    def send(self, fluids, external_force) :
        create_physics_command(PhysicsSolverUpdateCommand.CommandNameLabel)
        set_arg_int(PhysicsSolverUpdateCommand.IdLabel, self.id)
        fluid_ids = []
        for f in fluids :
            fluid_ids.append(f.id)
        set_arg_int_vector(PhysicsSolverUpdateCommand.FluidSceneIdsLabel, fluid_ids)
        set_arg_vector3df(PhysicsSolverUpdateCommand.ExternalForceLabel, external_force)
        is_ok = execute_command(self.scene.world)
        return is_ok

    def simulate(self) :
        create_physics_command(FluidSimulationCommand.CommandNameLabel)
        set_arg_int(FluidSimulationCommand.SolverIdLabel, self.id)
        is_ok = execute_command(self.scene.world)
        return is_ok
