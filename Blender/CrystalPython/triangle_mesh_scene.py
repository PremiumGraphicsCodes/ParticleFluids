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
        create_scene_command(scene_labels.TriangleMeshCreateCommand.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshCreateCommand.LayerLabel, 1)
        set_arg_triangle3dd_vector(scene_labels.TriangleMeshCreateCommand.TrianglesLabel, triangles)
        set_arg_string(scene_labels.TriangleMeshCreateCommand.NameLabel, name)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(scene_labels.TriangleMeshCreateCommand.NewIdLabel)
        return is_ok

    def get_triangles(self) :
        create_scene_command(scene_labels.TriangleMeshGetCommand.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshGetCommand.MeshIdLabel, self.id)
        set_arg_int(scene_labels.TriangleMeshGetCommand.LayerLabel, 1)
        is_ok = execute_command(self.scene.world)
        return get_result_triangle3dd_vector(scene_labels.TriangleMeshGetCommand.TrianglesLabel)

    def set_triangles(self, triangles):
        create_scene_command(scene_labels.TriangleMeshSetCommand.CommandNameLabel)
        set_arg_int(scene_labels.TriangleMeshSetCommand.MeshIdLabel, self.id)
        set_arg_triangle3dd_vector(scene_labels.TriangleMeshSetCommand.TrianglesLabel, triangles)
        is_ok = execute_command(self.scene.world)
        return is_ok
#   TrianglesLabel="Triangles"
#   NormalsLabel="Normals"
#   NameLabel="Name"