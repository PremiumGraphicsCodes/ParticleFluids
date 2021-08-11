import scene_labels
from CrystalPLI import *

class Scene :
    def __init__(self, world) :
        self.world = world

    def clear(self, layer) :
        create_scene_command(scene_labels.ClearLabels.CommandNameLabel);
        set_arg_int(scene_labels.ClearLabels.LayerLabel, layer);
        return execute_command(self.world);

    def delete(self, id, isItem):
        create_scene_command(scene_labels.DeleteLabels.CommandNameLabel)
        set_arg_int(scene_labels.DeleteLabels.IdLabel, id)
        set_arg_bool(scene_labels.DeleteLabels.IsItemLabel, isItem)
        return execute_command(self.world)   

class WireFrameScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty_wire_frame_scene(self, name, line_width, color, layer) :
        create_scene_command(scene_labels.WireFrameCreateLabels.WireFrameAddLabel)
        set_arg_string(scene_labels.WireFrameCreateLabels.NameLabel, name)
        set_arg_float(scene_labels.WireFrameCreateLabels.LineWidthLabel, line_width)
        set_arg_color4f(scene_labels.WireFrameCreateLabels.ColorLabel, color)
        set_arg_int(scene_labels.WireFrameCreateLabels.LayerLabel, layer)
        execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.WireFrameCreateLabels.NewIdLabel)
     