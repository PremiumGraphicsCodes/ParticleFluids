import CrystalPLI
import os
import vdb_labels
import vdb_command

from scene import Scene
from CrystalPLI import *

class VDBCommand :
    def __init__(self, scene) :
        self.scene = scene

    def init(self) :
        create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
        isOk = execute_command(self.scene.world)
        return isOk

    def read_vdb_file(self, filepath) :
        create_vdb_command(vdb_labels.VDBFileReadLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileReadLabels.FilePathLabel, filepath)
        execute_command(self.scene.world)
        newIds = get_result_int_vector(vdb_labels.VDBFileReadLabels.NewIdLabel)
        return newIds

    def write_vdb_file(self, filepath, particleSystemIds, volumeIds) :
        create_vdb_command(vdb_labels.VDBFileWriteLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBFileWriteLabels.FilePathLabel, filepath)
        set_arg_int_vector(vdb_labels.VDBFileWriteLabels.ParticleSystemIdsLabel, particleSystemIds)
        set_arg_int_vector(vdb_labels.VDBFileWriteLabels.VDBVolumeIdsLabel, volumeIds);
        execute_command(self.scene.world)

    def create_vdb_empty_points(self, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel);
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBPointsLabel)
        execute_command(self.scene.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId
    
    def create_vdb_points(self, positions, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBPointsLabel)
        set_arg_vector3dd_vector(vdb_labels.VDBSceneCreateLabels.PositionsLabel, positions)
        execute_command(self.scene.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId

    def create_vdb_mesh(self, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBMeshLabel)
        execute_command(self.scene.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId

    def create_vdb_volume(self, name) :
        create_vdb_command(vdb_labels.VDBSceneCreateLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBSceneCreateLabels.SceneTypeLabel, vdb_labels.VDBSceneCreateLabels.SceneType_VDBVolumeLabel)
        execute_command(self.scene.world)
        newId = get_result_int(vdb_labels.VDBSceneCreateLabels.NewIdLabel)
        return newId

    def write_obj_file(self, vdb_mesh_id, file_path) :
        create_vdb_command(vdb_labels.VDBOBJFileWriteLabels.CommandNameLabel)
        set_arg_int(vdb_labels.VDBOBJFileWriteLabels.VDBMeshIdLabel, vdb_mesh_id)
        set_arg_string(vdb_labels.VDBOBJFileWriteLabels.FilePathLabel, file_path)
        isOk = execute_command(self.scene.world)
        return isOk

    def read_obj_file(self, file_path) :
        create_vdb_command(vdb_labels.VDBOBJFileReadLabels.CommandNameLabel)
        set_arg_string(vdb_labels.VDBOBJFileReadLabels.FilePathLabel, file_path)
        isOk = execute_command(self.scene.world)
        if isOk == False :
            return -1
        newId = get_result_int(vdb_labels.VDBOBJFileReadLabels.VDBMeshIdLabel)
        return newId

    def convert_ps_to_volume(self, particle_system_id, vdb_volume_id, radius) :
        create_vdb_command(vdb_labels.VDBPSToVolumeLabels.CommandNameLabel)
        set_arg_int(vdb_labels.VDBPSToVolumeLabels.ParticleSystemIdLabel, particle_system_id)
        set_arg_int(vdb_labels.VDBPSToVolumeLabels.VolumeIdLabel, vdb_volume_id)
        set_arg_double(vdb_labels.VDBPSToVolumeLabels.RadiusLabel, radius)
        isOk = execute_command(self.scene.world)
        return isOk

    def convert_mesh_to_volume(self, mesh_id, vdb_volume_id, divideLength) :
        create_vdb_command(vdb_labels.VDBMeshToVolumeLabels.CommandNameLabel)
        set_arg_int(vdb_labels.VDBMeshToVolumeLabels.VDBMeshIdLabel, mesh_id)
        set_arg_int(vdb_labels.VDBMeshToVolumeLabels.VDBVolumeIdLabel, vdb_volume_id)
        set_arg_double(vdb_labels.VDBMeshToVolumeLabels.DivideLengthLabel, divideLength);
        isOk = execute_command(self.scene.world)
        return isOk
    
    def convert_volume_from_sparse_volume(self, sparse_volume_id, vdb_volume_id) :
        create_vdb_command(vdb_labels.ToVDBVolumeLabels.CommandNameLabel)
        set_arg_int(vdb_labels.ToVDBVolumeLabels.SparseVolumeIdLabel, sparse_volume_id)
        set_arg_int(vdb_labels.ToVDBVolumeLabels.VDBVolumeIdLabel, vdb_volume_id)
        isOk = execute_command(self.scene.world)
        return isOk

    def convert_volume_to_mesh(self, vdb_volume_id, vdb_mesh_id) :
        create_vdb_command(vdb_labels.VDBVolumeToMeshLabels.CommandNameLabel)
        set_arg_int(vdb_labels.VDBVolumeToMeshLabels.VolumeIdLabel, vdb_volume_id)
        set_arg_int(vdb_labels.VDBVolumeToMeshLabels.VDBMeshIdLabel, vdb_mesh_id)
        isOk = execute_command(self.scene.world)
        return isOk
    
    def convert_volume_to_particle_system(vdb_volume_Id, vdb_particle_system_id) :
        create_vdb_command(vdb_labels.VDBVolumeToPSLabels.CommandNameLabel)
        set_arg_int(vdb_labels.VDBVolumeToPSLabels.VDBVolumeIdLabel, vdb_volume_Id)
        set_arg_int(vdb_labels.VDBVolumeToPSLabels.VDBParticleSystemIdLabel, vdb_particle_system_id)
        isOk = command.Execute(world.Adapter)
        return isOk

    def convert_mesh_to_particle_system(mesh_id, particle_system_id, divide_length) :
        volume_id = create_vdb_volume("Volume", false)
        if not convert_mesh_to_volume(mesh_id, volume_id, divide_length * 0.5) :
            return False
        if not convert_volume_to_particle_system(volume_id, particle_system_id) :
            return False
        self.scene.Delete(volume_id)
        return True

