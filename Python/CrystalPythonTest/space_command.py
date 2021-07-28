import space_labels

from scene import *
from CrystalPython import *

class SpaceCommand :
    def __init__(self, world):
        self.world = world

    def create_sparse_volume(resolution, boundingBox, layer, name) :
        create_sparse_command(space_labels.SparseVolumeSceneCreateLabels.CommandNameLabel);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionXLabel, resolution[0]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionYLabel, resolution[1]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionZLabel, resolution[2]);
        set_arg_box3df(space_labels.SparseVolumeSceneCreateLabels.BoundingBoxLabel, boundingBox);
        set_arg_string(space_labels.SparseVolumeSceneCreateLabels.NameLabel, name);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.LayerLabel, layer);
        execute_command(self.world)
        newId = get_result_int(space_labels.SparseVolumeSceneCreateLabels.NewIdLabel);
        return newId

