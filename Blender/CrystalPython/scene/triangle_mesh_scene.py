from scene.scene_labels import *
from scene.scene import *
from CrystalPLI import *

class TriangleMeshScene :
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty(self, name) :
        triangles = Triangle3ddVector()
        return self.create(triangles, name)

    def create(self, triangles, name) :
        create_scene_command(TriangleMeshCreateCommand.CommandNameLabel)
        set_arg_triangle3dd_vector(TriangleMeshCreateCommand.TrianglesLabel, triangles)
        set_arg_string(TriangleMeshCreateCommand.NameLabel, name)
        is_ok = execute_command(self.scene.world)
        self.id = get_result_int(TriangleMeshCreateCommand.NewIdLabel)
        return is_ok

    def get_triangles(self) :
        create_scene_command(TriangleMeshGetCommand.CommandNameLabel)
        set_arg_int(TriangleMeshGetCommand.MeshIdLabel, self.id)
        is_ok = execute_command(self.scene.world)
        return get_result_triangle3dd_vector(TriangleMeshGetCommand.TrianglesLabel)

    def set_triangles(self, triangles):
        create_scene_command(TriangleMeshSetCommand.CommandNameLabel)
        set_arg_int(TriangleMeshSetCommand.MeshIdLabel, self.id)
        set_arg_triangle3dd_vector(TriangleMeshSetCommand.TrianglesLabel, triangles)
        is_ok = execute_command(self.scene.world)
        return is_ok
#   TrianglesLabel="Triangles"
#   NormalsLabel="Normals"
#   NameLabel="Name"