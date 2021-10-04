import scene_labels
from CrystalPLI import *

class Scene :
    def __init__(self, world) :
        self.world = world

    def clear(self, layer) :
        create_scene_command(scene_labels.ClearCommand.CommandNameLabel);
        set_arg_int(scene_labels.ClearCommand.LayerLabel, layer);
        return execute_command(self.world);

    def delete(self, id, isItem):
        create_scene_command(scene_labels.DeleteCommand.CommandNameLabel)
        set_arg_int(scene_labels.DeleteCommand.IdLabel, id)
        set_arg_bool(scene_labels.DeleteCommand.IsItemLabel, isItem)
        return execute_command(self.world)   

