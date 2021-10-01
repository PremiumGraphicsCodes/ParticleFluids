import scene_labels
from scene import *
from CrystalPLI import *

class TriangleMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty(self, name) :
        triangles = Triangle3ddVector()
        return self.create(triangles, name)

    def create(self, triangles, name) :
        create_scene_command(scene_labels.TriangleMeshCreateLabels.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshCreateLabels.LayerLabel, 1)
        set_arg_triangle3dd_vector(scene_labels.TriangleMeshCreateLabels.TrianglesLabel, triangles)
        set_arg_string(scene_labels.TriangleMeshCreateLabels.NameLabel, name)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.PolygonMeshCreateLabels.NewIdLabel)
        return is_ok

    def get_triangles(self) :
        create_scene_command(scene_labels.TriangleMeshGetLabels.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshGetLabels.MeshIdLabel, self.id)
        set_arg_int(scene_labels.TriangleMeshGetLabels.LayerLabel, 1)
        is_ok = execute_command(self.scene.world)
        return get_result_triangle3dd_vector(scene_labels.TriangleMeshGetLabels.TrianglesLabel)

    def set_triangles(self, triangles):
        create_scene_command(scene_labels.TriangleMeshSetLabels.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshSetLabels.MeshIdLabel, self.id)
        set_arg_triangle3dd_vector(scene_labels.TriangleMeshSetLabels.TrianglesLabel, triangles)
        is_ok = execute_command(self.scene.world)
        return is_ok
#   TrianglesLabel="Triangles"
#   NormalsLabel="Normals"
#   NameLabel="Name"