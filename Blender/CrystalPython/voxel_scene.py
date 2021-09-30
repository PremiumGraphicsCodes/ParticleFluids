import space_labels

from scene import *
from CrystalPLI import *

class GridData :
    def __init__(self) :
        self.res = []
        self.bb = Box3dd()
        self.values = []

class VoxelScene :    
    def __init__(self, scene) :
        self.scene = scene
        self.id = -1

    def create_empty_voxel(self, name) :
        resolution = [2,2,2]
        bb = Box3dd()
        return self.create_voxel(name, resolution, bb)

    def create_voxel(self, name, resolution, boundingBox) :
       create_space_command(space_labels.VoxelSceneCreateLabels.CommandNameLabel)
       set_arg_int(space_labels.VoxelSceneCreateLabels.ResolutionXLabel, resolution[0])
       set_arg_int(space_labels.VoxelSceneCreateLabels.ResolutionYLabel, resolution[1])
       set_arg_int(space_labels.VoxelSceneCreateLabels.ResolutionZLabel, resolution[2])
       set_arg_box3dd(space_labels.VoxelSceneCreateLabels.BoundingBoxLabel, boundingBox)
       set_arg_string(space_labels.VoxelSceneCreateLabels.NameLabel, name)
       set_arg_int(space_labels.VoxelSceneCreateLabels.LayerLabel, 1)
       is_ok = execute_command(self.scene.world)
       if not is_ok :
           return False
       self.id = get_result_int(space_labels.VoxelSceneCreateLabels.NewIdLabel);
       return True

    def set_voxel_nodes(self, nodes) :
        indicesX = []
        indicesY = []
        indicesZ = []
        values = []
        for node in nodes :
            indicesX.append(node.Index[0])
            indicesY.append(node.Index[1])
            indicesZ.append(node.Index[2])
            values.append(node.Value)

        create_space_command(space_labels.VoxelSetLabels.CommandNameLabel)
        set_arg_int(space_labels.VoxelSetLabels.VoxelIdLabel, self.Id)
        set_arg_int_vector(space_labels.VoxelSetLabels.IndicesXLabel, indicesX)
        set_arg_int_vector(space_labels.VoxelSetLabels.IndicesYLabel, indicesY)
        set_arg_int_vector(space_labels.VoxelSetLabels.IndicesZLabel, indicesZ)
        set_arg_bool_vector(space_labels.VoxelSetLabels.ValuesLabel, values)
        is_ok = command.Execute(world.Adapter)
        return is_ok

    def get_values(self):
        value = []
        create_space_command(space_labels.VoxelGetLabels.CommandNameLabel)
        set_arg_int(space_labels.VoxelGetLabels.VoxelIdLabel, self.id)
        execute_command(self.scene.world)
        xres = get_result_int(space_labels.VoxelGetLabels.ResolutionXLabel)
        yres = get_result_int(space_labels.VoxelGetLabels.ResolutionYLabel)
        zres = get_result_int(space_labels.VoxelGetLabels.ResolutionZLabel)
        bb = get_result_box3dd(space_labels.VoxelGetLabels.BoundingBoxLabel)
        values = get_result_bool_vector(space_labels.VoxelGetLabels.ValuesLabel)
        data = GridData()
        data.res = [xres, yres, zres]
        data.bb = bb;
        data.values = values
        return data

    def convert_to_ps(self, psId) :
        create_space_command(space_labels.VoxelToPSLabels.CommandNameLabel)
        set_arg_int(space_labels.VoxelToPSLabels.VoxelIdLabel, self.id)
        set_arg_int(space_labels.VoxelToPSLabels.PSIdLabel, psId)
        is_ok = execute_command(self.scene.world)
        return is_ok

class Voxelizer :
    def __init__(self, scene) :
        self.scene = scene

    def voxelize(self, mesh_id, voxel_id, divide_length) :
        create_space_command(space_labels.VoxelizerLabels.CommandNameLabel)
        set_arg_int(space_labels.VoxelizerLabels.MeshIdLabel, mesh_id)
        set_arg_int(space_labels.VoxelizerLabels.VoxelIdLabel, voxel_id)
        set_arg_float(space_labels.VoxelizerLabels.DivideLengthLabel, divide_length)
        is_ok = execute_command(self.scene.world)
        return is_ok
