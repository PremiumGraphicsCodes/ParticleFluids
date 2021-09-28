import space_labels

from scene import *
from CrystalPLI import *

class VoxelScene :    
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

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
