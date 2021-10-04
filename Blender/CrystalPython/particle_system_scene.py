import scene_labels
from scene import *
from CrystalPLI import *

class ParticleSystemScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty(self, name) :
        positions = Vector3ddVector()
        color = ColorRGBAf()
        return self.create(positions,name,1.0, color, 1)

    def create(self, positions, name, point_size, color, layer) :
        create_scene_command(scene_labels.ParticleSystemCreateCommand.ParticleSystemAddLabel)
        set_arg_vector3dd_vector(scene_labels.ParticleSystemCreateCommand.PositionsLabel, positions)
        set_arg_string(scene_labels.ParticleSystemCreateCommand.NameLabel, name)
        set_arg_float(scene_labels.ParticleSystemCreateCommand.PointSizeLabel, point_size)
        set_arg_color4f(scene_labels.ParticleSystemCreateCommand.ColorLabel, color)
        set_arg_int(scene_labels.ParticleSystemCreateCommand.LayerLabel, layer)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.ParticleSystemCreateCommand.NewIdLabel)
        return is_ok

    def export_pcd_file(self, file_path) :
        create_scene_command(scene_labels.PCDFileExportCommand.CommandNameLabel)
        set_arg_int_vector(scene_labels.PCDFileExportCommand.IdsLabel, [self.id])
        set_arg_string(scene_labels.PCDFileExportCommand.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        return is_ok

    def import_pcd_file(self, file_path) :
        create_scene_command(scene_labels.PCDFileImportCommand.CommandNameLabel)
        set_arg_string(scene_labels.PCDFileImportCommand.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PCDFileImportCommand.NewIdLabel)
        return is_ok

    def get_positions(self) :
        create_scene_command(scene_labels.ParticleSystemGetCommand.CommandNameLabel)
        set_arg_int(scene_labels.ParticleSystemGetCommand.PSIdLabel, self.id)
        is_ok = execute_command(self.scene.world)
        return get_result_vector3dd_vector(scene_labels.ParticleSystemGetCommand.PositionsLabel)

    def set_positions(self, positions):
        create_scene_command(scene_labels.ParticleSystemSetCommand.CommandNameLabel)
        set_arg_int(scene_labels.ParticleSystemSetCommand.IdLabel, self.id)
        set_arg_vector3dd_vector(scene_labels.ParticleSystemSetCommand.PositionsLabel, positions)
        is_ok = execute_command(self.scene.world)
        return is_ok