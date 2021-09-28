import scene_labels
from scene import *
from CrystalPLI import *

class TriangleMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create(self, triangles, name, layer) :
        create_scene_command(scene_labels.TriangleMeshCreateLabels.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshSceneCreateLabels.LayerLabel, layer)
        set_arg_triangle3dd_vector(scene_labels.TriangleMeshCreateLabels.TrianglesLabel, triangles)
        set_arg_string(scene_labels.TriangleMeshCreateLabels.NameLabel, name)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.NewIdLabel)
        return is_ok
