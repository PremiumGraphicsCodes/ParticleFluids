using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using System.Collections.Generic;

namespace FluidStudio.VDB
{

    public class VDBModel
    {
        public enum VDBType
        {
            None,
            Point,
            Mesh,
            Volume
        }

        private static string VDBPointLabel = "VDBParticleSystem";
        private static string VDBVolumeLabel = "VDBVolume";
        private static string VDBMeshLabel = "VDBMesh";

        public string ToString(VDBType type)
        {
            switch (type)
            {
                case VDBType.Point:
                    return VDBPointLabel;
                case VDBType.Volume:
                    return VDBVolumeLabel;
                case VDBType.Mesh:
                    return VDBMeshLabel;
                default:
                    System.Diagnostics.Debug.Assert(false);
                    return "";
            }
        }

        public VDBType GetVDBType(int id, SceneList scene)
        {
            return FromString(scene.GetSceneTypeName(id));
        }

        public VDBType FromString(string str)
        {
            if(str == VDBPointLabel)
            {
                return VDBType.Point;
            }
            else if(str == VDBVolumeLabel)
            {
                return VDBType.Volume;
            }
            else if(str == VDBMeshLabel)
            {
                return VDBType.Mesh;
            }
            System.Diagnostics.Debug.Assert(false);
            return VDBType.None;
        }

        public bool Init(SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBInitLabels.CommandNameLabel);
            return command.Execute(world.Adapter);
        }

        public List<int> Read(string filePath, SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBFileReadLabels.CommandNameLabel);
            command.SetArg(PG.VDBFileReadLabels.FilePathLabel, filePath);
            if (!command.Execute(world.Adapter))
            {
                return new List<int>();
            }
            var newIds = command.GetResult<List<int>>(PG.VDBFileReadLabels.NewIdLabel);
            return newIds;
        }

        public bool Write(string filePath, SceneList world, List<int> particleSystemIds, List<int> volumeIds)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBFileWriteLabels.CommandNameLabel);
            command.SetArg(PG.VDBFileWriteLabels.FilePathLabel, filePath);
            command.SetArg(PG.VDBFileWriteLabels.ParticleSystemIdsLabel, particleSystemIds);
            command.SetArg(PG.VDBFileWriteLabels.VDBVolumeIdsLabel, volumeIds);
            return command.Execute(world.Adapter);
        }

        public int CreateVDBPoints(SceneList world, List<Vector3d> positions, string name)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.VDBSceneCreateLabels.SceneTypeLabel, PG.VDBSceneCreateLabels.SceneType_VDBPointsLabel);
            command.SetArg(PG.VDBSceneCreateLabels.PositionsLabel, positions);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VDBSceneCreateLabels.NewIdLabel);
            var scene = new SceneModel();
            scene.Id.Value = newId;
            scene.Name.Value = name;
            world.SetName(newId, name);
            scene.SceneType = new PG.Core.SceneType(VDBPointLabel);
            world.Add(scene);
            return newId;
        }

        public int CreateVDBPoints(SceneList world, string name)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.VDBSceneCreateLabels.SceneTypeLabel, PG.VDBSceneCreateLabels.SceneType_VDBPointsLabel);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VDBSceneCreateLabels.NewIdLabel);
            var scene = new SceneModel();
            scene.Id.Value = newId;
            scene.Name.Value = name;
            world.SetName(newId, name);
            scene.SceneType = new PG.Core.SceneType(VDBPointLabel);
            world.Add(scene);
            return newId;
        }


        public int CreateVDBMesh(SceneList world, string name)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.VDBSceneCreateLabels.SceneTypeLabel, PG.VDBSceneCreateLabels.SceneType_VDBMeshLabel);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VDBSceneCreateLabels.NewIdLabel);
            var scene = new SceneModel();
            scene.Id.Value = newId;
            scene.Name.Value = name;
            scene.SceneType = new PG.Core.SceneType(VDBMeshLabel);
            world.SetName(newId, name);
            world.Add(scene);
            return newId;
        }

        public int CreateVDBVolume(SceneList world, string name, bool doAddToList)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBSceneCreateLabels.CommandNameLabel);
            command.SetArg(PG.VDBSceneCreateLabels.SceneTypeLabel, PG.VDBSceneCreateLabels.SceneType_VDBVolumeLabel);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VDBSceneCreateLabels.NewIdLabel);
            world.SetName(newId, name);
            if (doAddToList)
            {
                var scene = new SceneModel();
                scene.Id.Value = newId;
                scene.Name.Value = name;
                scene.SceneType = new PG.Core.SceneType(VDBVolumeLabel);
                world.Add(scene);
            }
            return newId;
        }

        public bool ConvertPSToVolume(int particleSystemId, int vdbVolumeId, SceneList world, double radius)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBPSToVolumeLabels.CommandNameLabel);
            command.SetArg(PG.VDBPSToVolumeLabels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(PG.VDBPSToVolumeLabels.VolumeIdLabel, vdbVolumeId);
            command.SetArg(PG.VDBPSToVolumeLabels.RadiusLabel, radius);
            return command.Execute(world.Adapter);
        }

        public bool ConvertMeshToVolume(int meshId, int vdbVolumeId, SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBMeshToVolumeLabels.CommandNameLabel);
            command.SetArg(PG.VDBMeshToVolumeLabels.VDBMeshIdLabel, meshId);
            command.SetArg(PG.VDBMeshToVolumeLabels.VDBVolumeIdLabel, vdbVolumeId);
            return command.Execute(world.Adapter);
        }

        public bool ConvertVolumeToPS(int vdbVolumeId, int vdbPSId, SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBVolumeToPSLabels.CommandNameLabel);
            command.SetArg(PG.VDBVolumeToPSLabels.VDBVolumeIdLabel, vdbVolumeId);
            command.SetArg(PG.VDBVolumeToPSLabels.VDBParticleSystemIdLabel, vdbPSId);
            return command.Execute(world.Adapter);
        }

        public bool WriteOBJ(SceneList world, int vdbMeshId, string filePath)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBOBJFileWriteLabels.CommandNameLabel);
            command.SetArg(PG.VDBOBJFileWriteLabels.VDBMeshIdLabel, vdbMeshId);
            command.SetArg(PG.VDBOBJFileWriteLabels.FilePathLabel, filePath);
            return command.Execute(world.Adapter);
        }

        public int ReadOBJ(SceneList world, string filePath)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBOBJFileReadLabels.CommandNameLabel);
            command.SetArg(PG.VDBOBJFileReadLabels.FilePathLabel, filePath);
            var isOk = command.Execute(world.Adapter);
            if (!isOk)
            {
                return -1;
            }
            return command.GetResult<int>(PG.VDBOBJFileReadLabels.VDBMeshIdLabel);
        }

        public bool ExportAll(SceneList world, string filePath)
        {
            var vdbPsIds = new List<int>();
            var vdbVolumeIds = new List<int>();
            foreach(var scene in world.Scenes)
            {
                var s = world.GetSceneTypeName(scene.Id.Value);
                if(s == VDBPointLabel)
                {
                    vdbPsIds.Add(scene.Id.Value);
                }
                else if(s == VDBVolumeLabel)
                {
                    vdbVolumeIds.Add(scene.Id.Value);
                }
            }
            var command = new PG.CLI.VDBCommand(PG.VDBFileWriteLabels.CommandNameLabel);
            command.SetArg(PG.VDBFileWriteLabels.ParticleSystemIdsLabel, vdbPsIds);
            command.SetArg(PG.VDBFileWriteLabels.VDBVolumeIdsLabel, vdbVolumeIds);
            command.SetArg(PG.VDBFileWriteLabels.FilePathLabel, filePath);
            return command.Execute(world.Adapter);
        }
    }
}
