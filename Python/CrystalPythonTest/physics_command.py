import physics_labels
from vdb_command import Scene
from CrystalPython import *

class PhysicsCommand :
    def __init__(self, world) :
        self.world = world

    def create_solver(self) :
        create_physics_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command(self.world)
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
        return newId

