import space_labels

from scene import *
from CrystalPLI import *

class SparseVolumeNode :
    def __init__(self) :
        self.indices = []
        self.value = 0.0

class VoxelNode :
    def __init__(self) :
        self.indices = []
        self.value = false

class SpaceCommand :
    def __init__(self, scene):
        self.scene = scene

    def create_sparse_volume(self, resolution, boundingBox, layer, name) :
        create_space_command(space_labels.SparseVolumeSceneCreateLabels.CommandNameLabel);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionXLabel, resolution[0]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionYLabel, resolution[1]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionZLabel, resolution[2]);
        set_arg_box3dd(space_labels.SparseVolumeSceneCreateLabels.BoundingBoxLabel, boundingBox);
        set_arg_string(space_labels.SparseVolumeSceneCreateLabels.NameLabel, name);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.LayerLabel, layer);
        execute_command(self.scene.world)
        newId = get_result_int(space_labels.SparseVolumeSceneCreateLabels.NewIdLabel);
        return newId

    def set_sparse_nodes(self, sparse_volume_id, nodes) :
        indicesX = [];
        indicesY = [];
        indicesZ = [];
        values = [];
        for node in nodes :
            indicesX.append(node.Index[0])
            indicesY.append(node.Index[1])
            indicesZ.append(node.Index[2])
            values.append(node.Value)

        create_space_command(space_labels.SparseVolumeNodeSetLabels.CommandNameLabel)
        set_arg_int(space_labels.SparseVolumeNodeSetLabels.SparseVolumeIdLabel, sparseVolumeId)
        set_arg_int_vector(space_labels.SparseVolumeNodeSetLabels.IndicesXLabel, indicesX)
        set_arg_int_vector(space_labels.SparseVolumeNodeSetLabels.IndicesYLabel, indicesY)
        set_arg_int_vector(space_labels.SparseVolumeNodeSetLabels.IndicesZLabel, indicesZ)
        set_arg_float_vector(space_labels.SparseVolumeNodeSetLabels.ValuesLabel, values);
        is_ok = execute_command(self.scene.world)
        return is_ok

#   def create_voxel(name, layer) :
#        resolution = [1,1,1]
#        box = Box3dd(Vector3dd(0, 0, 0), Vector3dd(1, 1, 1))
#        return CreateVoxel(name, resolution, box, layer)

    def create_voxel(self, name, resolution, boundingBox, layer) :
       create_space_command(space_labels.VoxelSceneCreateLabels.CommandNameLabel)
       set_arg_int(space_labels.VoxelSceneCreateLabels.ResolutionXLabel, resolution[0])
       set_arg_int(space_labels.VoxelSceneCreateLabels.ResolutionYLabel, resolution[1])
       set_arg_int(space_labels.VoxelSceneCreateLabels.ResolutionZLabel, resolution[2])
       set_arg_box3dd(space_labels.VoxelSceneCreateLabels.BoundingBoxLabel, boundingBox)
       set_arg_string(space_labels.VoxelSceneCreateLabels.NameLabel, name)
       set_arg_int(space_labels.VoxelSceneCreateLabels.LayerLabel, layer)
       execute_command(self.scene.world)
       new_id = get_result_int(space_labels.VoxelSceneCreateLabels.NewIdLabel);
       return new_id

    def set_voxel_nodes(voxel_id, nodes) :
        indicesX = []
        indicesY = []
        indicesZ = []
        values = []
        for node in nodes :
            indicesX.append(node.Index[0])
            indicesY.append(node.Index[1])
            indicesZ.append(node.Index[2])
            values.append(node.Value)

        create_space_command(space_labels.VoxelNodeSetLabels.CommandNameLabel)
        set_arg_int(space_labels.VoxelNodeSetLabels.VoxelIdLabel, voxelId)
        set_arg_int_vector(space_labels.VoxelNodeSetLabels.IndicesXLabel, indicesX)
        set_arg_int_vector(space_labels.VoxelNodeSetLabels.IndicesYLabel, indicesY)
        set_arg_int_vector(space_labels.VoxelNodeSetLabels.IndicesZLabel, indicesZ)
        set_arg_bool_vector(space_labels.VoxelNodeSetLabels.ValuesLabel, values)
        is_ok = command.Execute(world.Adapter)
        return is_ok

    def voxelize(mesh_id, particle_system_id, divide_length) :
        create_space_command(space_labels.VoxelizerLabels.CommandNameLabel)
        set_arg_int(space_labels.VoxelizerLabels.MeshIdLabel, mesh_id)
        set_arg_int(space_labels.VoxelizerLabels.PSIdLabel, particle_system_id)
        set_arg_float(space_labels.VoxelizerLabels.DivideLengthLabel, divide_length)
        is_ok = command.Execute(world.Adapter)
        return is_ok