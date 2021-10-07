from physics.physics_labels import *
from scene.scene import Scene
from CrystalPLI import *

class SolverScene :
    def __init__(self, scene) :
        self.scene = scene

    def create(self) :
        create_physics_command(PhysicsSolverCreateCommand.CommandNameLabel)
        isOk = execute_command(self.scene.world)
        #self.assertTrue(isOk)
        newId = get_result_int(PhysicsSolverCreateCommand.NewIdLabel)
        return newId
