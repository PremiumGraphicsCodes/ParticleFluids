from scene.scene_labels import TXTFileImportCommand, TXTFileExportCommand
from scene.scene import *
import CrystalPLI

class FileIO :
    def import_txt(scene, particle_system_id, file_path) :
        create_scene_command(TXTFileImportCommand.CommandNameLabel)
        set_arg_int(TXTFileImportCommand.IdLabel, particle_system_id)
        set_arg_string(TXTFileImportCommand.FilePathLabel, file_path)
        is_ok = execute_command(scene.world)
        return is_ok

    def export_txt(scene, particle_system_ids, file_path) :
        create_scene_command(TXTFileExportCommand.CommandNameLabel)
        set_arg_int_vector(TXTFileExportCommand.IdsLabel, particle_system_ids)
        set_arg_string(TXTFileExportCommand.FilePathLabel, file_path)
        is_ok = execute_command(scene.world)
        return is_ok