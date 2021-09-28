import scene_labels
from scene import *
from CrystalPLI import *

class TriangleMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create(self, layer) :
        create_scene_command(scene_labels.TriangleMeshCreateLabels.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshSceneCreateLabels.LayerLabel, layer)
#        set_arg_vector3dd_vector(scene_labels.PolygonMeshCreateLabels.PositionsLabel, positions)
#        set_arg_vector3dd_vector(scene_labels.PolygonMeshCreateLabels.NormalsLabel, normals)
#        set_arg_
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.NewIdLabel)
        return is_ok
