import scene_labels
from scene import *
from CrystalPLI import *

class WireFrameScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty_wire_frame_scene(self, name, line_width, color, layer) :
        create_scene_command(scene_labels.WireFrameCreateCommand.WireFrameAddLabel)
        set_arg_string(scene_labels.WireFrameCreateCommand.NameLabel, name)
        set_arg_float(scene_labels.WireFrameCreateCommand.LineWidthLabel, line_width)
        set_arg_color4f(scene_labels.WireFrameCreateCommand.ColorLabel, color)
        set_arg_int(scene_labels.WireFrameCreateCommand.LayerLabel, layer)
        execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.WireFrameCreateCommand.NewIdLabel)
     
