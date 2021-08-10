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

    def create_particle_system_scene(self, positions, name, point_size, color, layer) :
        create_scene_command(scene_labels.ParticleSystemCreateLabels.ParticleSystemAddLabel)
        set_arg_vector3dd_vector(scene_labels.ParticleSystemCreateLabels.PositionsLabel, positions)
        set_arg_string(scene_labels.ParticleSystemCreateLabels.NameLabel, name)
        set_arg_float(scene_labels.ParticleSystemCreateLabels.PointSizeLabel, point_size)
        set_arg_color4f(scene_labels.ParticleSystemCreateLabels.ColorLabel, color)
        set_arg_int(scene_labels.ParticleSystemCreateLabels.LayerLabel, layer)
        execute_command(self.world)
        newId = get_result_int(scene_labels.ParticleSystemCreateLabels.NewIdLabel)
        return newId

    def create_empty_wire_frame_scene(self, name, line_width, color, layer) :
        create_scene_command(scene_labels.WireFrameCreateLabels.WireFrameAddLabel)
        set_arg_string(scene_labels.WireFrameCreateLabels.NameLabel, name)
        set_arg_float(scene_labels.WireFrameCreateLabels.LineWidthLabel, line_width)
        set_arg_color4f(scene_labels.WireFrameCreateLabels.ColorLabel, color)
        set_arg_int(scene_labels.WireFrameCreateLabels.LayerLabel, layer)
        execute_command(self.world)
        new_id = get_result_int(scene_labels.WireFrameCreateLabels.NewIdLabel)
        return new_id
        