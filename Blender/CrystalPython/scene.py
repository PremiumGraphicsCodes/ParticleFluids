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
     
class PolygonMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty_polygon_mesh_scene(self, name, layer) :
        create_scene_command(scene_labels.PolygonMeshCreateLabels.CommandNameLabel)
        set_arg_string(scene_labels.PolygonMeshCreateLabels.NameLabel, name)
        set_arg_int(scene_labels.PolygonMeshCreateLabels.LayerLabel, layer)
        execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.NewIdLabel)

    def create_polygon_mesh_scene(self, name, positions, normals, texcoords, layer) :
        create_scene_command(scene_labels.PolygonMeshCreateLabels.CommandNameLabel)
        set_arg_string(scene_labels.PolygonMeshCreateLabels.NameLabel, name)
        set_arg_int(scene_labels.PolygonMeshCreateLabels.LayerLabel, layer)
        set_arg_vector3dd_vector(scene_labels.PolygonMeshCreateLabels.PositionsLabel, positions)
 #        execute_command(self.world)
#        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.LayerLabel, layer)
