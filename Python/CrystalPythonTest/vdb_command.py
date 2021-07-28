import CrystalPython
import unittest
import os
import scene_labels
import space_labels
import physics_labels
import vdb_labels
import vdb_command

from CrystalPython import *

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

class SpaceCommand :
    def __init__(self, world):
        self.world = world

    def create_sparse_volume(resolution, boundingBox, layer, name) :
        create_sparse_command(space_labels.SparseVolumeSceneCreateLabels.CommandNameLabel);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionXLabel, resolution[0]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionYLabel, resolution[1]);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.ResolutionZLabel, resolution[2]);
        set_arg_box3df(space_labels.SparseVolumeSceneCreateLabels.BoundingBoxLabel, boundingBox);
        set_arg_string(space_labels.SparseVolumeSceneCreateLabels.NameLabel, name);
        set_arg_int(space_labels.SparseVolumeSceneCreateLabels.LayerLabel, layer);
        execute_command(self.world)
        newId = get_result_int(space_labels.SparseVolumeSceneCreateLabels.NewIdLabel);
        return newId


class PhysicsCommand :
    def __init__(self, world) :
        self.world = world

    def create_solver(self) :
        create_physics_command(physics_labels.PhysicsSolverCreateLabels.CommandNameLabel)
        isOk = execute_command(self.world)
        #self.assertTrue(isOk)
        newId = get_result_int(physics_labels.PhysicsSolverCreateLabels.NewIdLabel)
        return newId


class VDBCommand :
    def __init__(self, scene) :
        self.scene = scene
 #      create_vdb_command(vdb_labels.VDBInitLabels.CommandNameLabel)
 #       isOk = execute_command(self.world)

    def init(self) :
#        self.world = world
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
        if not convert_mesh_to_volume(mesh_id, volumeId, divideLength * 0.5) :
            return False;
#            }
#            if(!ConvertVolumeToPS(volumeId, psId))
#            {
#                return false;
#            }
#            world.Delete(volumeId);
#            return true;
#       }

