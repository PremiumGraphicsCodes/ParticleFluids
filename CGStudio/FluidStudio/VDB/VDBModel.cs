using PG.Control.OpenGL;
using PG.Scene;
using System.Collections.Generic;

namespace FluidStudio.VDB
{
    public class VDBModel
    {
        public bool Init(SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBInitLabels.CommandNameLabel);
            return command.Execute(world.Adapter);
        }

        public bool Read(string filePath, SceneList world, Canvas3d canvas)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBFileReadLabels.CommandNameLabel);
            command.SetArg(PG.VDBFileReadLabels.FilePathLabel, filePath);
            if (!command.Execute(world.Adapter))
            {
                return false;
            }
            var newIds = command.GetResult<List<int>>(PG.VDBFileReadLabels.NewIdLabel);
            foreach(var id in newIds)
            {
                canvas.BuildShader(world, id);
            }
            canvas.Render();
            return true;
        }

        public bool Write(string filePath, SceneList world, List<int> particleSystemIds)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBFileWriteLabels.CommandNameLabel);
            command.SetArg(PG.VDBFileWriteLabels.FilePathLabel, filePath);
            command.SetArg(PG.VDBFileWriteLabels.ParticleSystemIdsLabel, particleSystemIds);
            return command.Execute(world.Adapter);
        }

        public int CreateVDBMesh(SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBMeshCreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(PG.VDBMeshCreateLabels.NewVDBMeshIdLabel);
            var scene = new SceneModel();
            scene.Id.Value = newId;
            scene.Name.Value = "VDBMesh";
            world.Add(scene);
            return newId;
        }

        public bool BuildMesh(int particleSystemId, int vdbMeshId, SceneList world, double radius)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBParticleSystemToMeshLabels.CommandNameLabel);
            command.SetArg(PG.VDBParticleSystemToMeshLabels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(PG.VDBParticleSystemToMeshLabels.VDBMeshIdLabel, vdbMeshId);
            command.SetArg(PG.VDBParticleSystemToMeshLabels.RadiusLabel, radius);
            return command.Execute(world.Adapter);
        }

        public bool WriteOBJ(SceneList world, int vdbMeshId, string filePath)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBOBJFileWriteLabels.CommandNameLabel);
            command.SetArg(PG.VDBOBJFileWriteLabels.VDBMeshIdLabel, vdbMeshId);
            command.SetArg(PG.VDBOBJFileWriteLabels.FilePathLabel, filePath);
            return command.Execute(world.Adapter);
        }
    }
}
