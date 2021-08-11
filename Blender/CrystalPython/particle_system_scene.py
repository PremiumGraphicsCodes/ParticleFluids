import scene_labels
from scene import *
from CrystalPLI import *

class ParticleSystemScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create(self, positions, name, point_size, color, layer) :
        create_scene_command(scene_labels.ParticleSystemCreateLabels.ParticleSystemAddLabel)
        set_arg_vector3dd_vector(scene_labels.ParticleSystemCreateLabels.PositionsLabel, positions)
        set_arg_string(scene_labels.ParticleSystemCreateLabels.NameLabel, name)
        set_arg_float(scene_labels.ParticleSystemCreateLabels.PointSizeLabel, point_size)
        set_arg_color4f(scene_labels.ParticleSystemCreateLabels.ColorLabel, color)
        set_arg_int(scene_labels.ParticleSystemCreateLabels.LayerLabel, layer)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.ParticleSystemCreateLabels.NewIdLabel)
        return is_ok

    def export_pcd_file(self, file_path) :
        create_scene_command(scene_labels.PCDFileExportLabels.CommandNameLabel)
        set_arg_int_vector(scene_labels.PCDFileExportLabels.IdsLabel, [self.id])
        set_arg_string(scene_labels.PCDFileExportLabels.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        return is_ok

    def import_pcd_file(self, file_path) :
        create_scene_command(scene_labels.PCDFileImportLabels.CommandNameLabel)
        set_arg_string(scene_labels.PCDFileImportLabels.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PCDFileImportLabels.NewIdLabel)
        return is_ok

