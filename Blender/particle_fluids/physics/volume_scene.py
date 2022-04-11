from physics.physics_labels import FluidVolumeSceneCreateCommand
from scene.scene import Scene
from CrystalPLI import *

class VolumeScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = 0
        self.name = ""

    def create(self) :
        create_physics_command(FluidVolumeSceneCreateCommand.CommandNameLabel)
        execute_command(self.scene.world)
        self.id = get_result_int(FluidVolumeSceneCreateCommand.NewIdLabel)

