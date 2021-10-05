import physics_labels
from scene import Scene
from CrystalPLI import *

class CSGBoundaryScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = 0
        self.name = ""
        self.bounding_box = Box3dd()

    def create(self) :
        create_physics_command(physics_labels.CSGBoundarySceneCreateCommand.CommandNameLabel)
        execute_command(self.scene.world)
        self.id = get_result_int(physics_labels.FluidSceneCreateCommand.NewIdLabel)

    def send(self) :
        create_physics_command(physics_labels.CSGBoundarySceneUpdateCommand.CommandNameLabel)
        set_arg_int(physics_labels.CSGBoundarySceneUpdateCommand.IdLabel, self.id)
        set_arg_string(physics_labels.CSGBoundarySceneUpdateCommand.NameLabel, self.name)
        set_arg_box3dd(physics_labels.CSGBoundarySceneUpdateCommand.BoundingBoxLabel, self.bounding_box)
        is_ok = execute_command(self.scene.world)
        return is_ok
    
    def delete(self) :
        self.scene.delete(self.id, False)
