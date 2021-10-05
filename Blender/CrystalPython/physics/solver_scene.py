import physics_labels
from scene import Scene
from CrystalPLI import *

class SolverScene :
    def __init__(self, scene) :
        self.scene = scene

    def create(self) :
        create_physics_command(physics_labels.PhysicsSolverCreateCommand.CommandNameLabel)
        isOk = execute_command(self.scene.world)
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateCommand.NewIdLabel)
        return newId
