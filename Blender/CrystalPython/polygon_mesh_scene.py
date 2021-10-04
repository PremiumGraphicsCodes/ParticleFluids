import scene_labels
from scene import *
from CrystalPLI import *

class PolygonMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty_polygon_mesh_scene(self, name, layer) :
        create_scene_command(scene_labels.PolygonMeshCreateCommand.CommandNameLabel)
        set_arg_string(scene_labels.PolygonMeshCreateCommand.NameLabel, name)
        set_arg_int(scene_labels.PolygonMeshCreateCommand.LayerLabel, layer)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateCommand.NewIdLabel)
        return is_ok

    def create_polygon_mesh_scene(self, name, positions, normals, texcoords, layer) :
        create_scene_command(scene_labels.PolygonMeshCreateCommand.CommandNameLabel)
        set_arg_string(scene_labels.PolygonMeshCreateCommand.NameLabel, name)
        set_arg_int(scene_labels.PolygonMeshCreateCommand.LayerLabel, layer)
        set_arg_vector3dd_vector(scene_labels.PolygonMeshCreateCommand.PositionsLabel, positions)
        set_arg_vector3dd_vector(scene_labels.PolygonMeshCreateCommand.NormalsLabel, normals)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateCommand.NewIdLabel)
        return is_ok

    def add_verticies(self, positionIds, normalIds, texCoordIds) :
        create_scene_command(scene_labels.PolygonMeshAddVerticesCommand.CommandNameLabel)
        set_arg_int(scene_labels.PolygonMeshAddVerticesCommand.PolygonMeshIdLabel, self.id)
        set_arg_int_vector(scene_labels.PolygonMeshAddVerticesCommand.PositionIdsLabel, positionIds)
        set_arg_int_vector(scene_labels.PolygonMeshAddVerticesCommand.NormalIdsLabel, normalIds)
        set_arg_int_vector(scene_labels.PolygonMeshAddVerticesCommand.TexCoordIdsLabel, texCoordIds)
        is_ok = execute_command(self.world)
        return is_ok

    def add_faces(self, vertexIds) :
        create_scene_command(scene_labels.PolygonMeshAddFacesCommand.CommandNameLabel)
        set_arg_int(scene_labels.PolygonMeshAddFacesCommand.PolygonMeshIdLabel, self.id)
        set_arg_int_vector(scene_labels.PolygonMeshAddFacesCommand.VertexIdsLabel, vertexIds)
        is_ok = execute_command(self.world)
        return is_ok

    def export_obj_file(self, file_path) :
        create_scene_command(scene_labels.OBJFileExportCommand.CommandNameLabel)
        set_arg_int_vector(scene_labels.OBJFileExportCommand.IdsLabel, [id])
        set_arg_string(scene_labels.OBJFileExportCommand.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        return is_ok

    def import_obj_file(self, file_path) :
        create_scene_command(scene_labels.OBJFileImportCommand.CommandNameLabel)
        set_arg_string(scene_labels.OBJFileImportCommand.FilePathLabel, file_path)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.OBJFileImportCommand.NewIdLabel)
        return is_ok


