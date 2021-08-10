import scene_labels
from scene import *
from CrystalPLI import *

class PolygonMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty_polygon_mesh_scene(self, name, layer) :
        create_scene_command(scene_labels.PolygonMeshCreateLabels.CommandNameLabel)
        set_arg_string(scene_labels.PolygonMeshCreateLabels.NameLabel, name)
        set_arg_int(scene_labels.PolygonMeshCreateLabels.LayerLabel, layer)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.NewIdLabel)
        return is_ok

    def create_polygon_mesh_scene(self, name, positions, normals, texcoords, layer) :
        create_scene_command(scene_labels.PolygonMeshCreateLabels.CommandNameLabel)
        set_arg_string(scene_labels.PolygonMeshCreateLabels.NameLabel, name)
        set_arg_int(scene_labels.PolygonMeshCreateLabels.LayerLabel, layer)
        set_arg_vector3dd_vector(scene_labels.PolygonMeshCreateLabels.PositionsLabel, positions)
        is_ok = execute_command(self.world)
        return is_ok

    def add_verticies(self, positionIds, normalIds, texCoordIds) :
        create_scene_command(scene_labels.PolygonMeshAddVerticesLabels.CommandNameLabel)
        set_arg_int_vector(scene_labels.PolygonMeshAddVerticesLabels.PositionIdsLabel, positionIds)
        set_arg_int_vector(scene_labels.PolygonMeshAddVerticesLabels.NormalIdsLabel, normalIds)
        set_arg_int_vector(scene_labels.PolygonMeshAddVerticesLabels.TexCoordIdsLabel, texCoordIds)
        is_ok = execute_command(self.world)
        return is_ok

#        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.LayerLabel, layer)

    def export_obj_file(self, file_path) :
        create_scene_command(scene_labels.OBJFileExportLabels.CommandNameLabel)
        set_arg_int_vector(scene_labels.OBJFileExportLabels.IdsLabel, [id])
        set_arg_string(scene_labels.OBJFileExportLabels.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        return is_ok

#    def import_obj_file(self, file_path) :
#        create_scene_command(scene_labels.PCDFileImportLabels.CommandNameLabel)
#        set_arg_string(scene_labels.PCDFileImportLabels.FilePathLabel, file_path)
#        is_ok = execute_command(self.scene.world)
#        self.id = get_result_int(scene_labels.PCDFileImportLabels.NewIdLabel)
#        return is_ok


