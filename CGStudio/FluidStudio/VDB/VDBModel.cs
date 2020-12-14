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

        public bool BuildMesh(int particleSystemId, int meshId, SceneList world)
        {
            var command = new PG.CLI.VDBCommand(PG.VDBParticleSystemToMeshLabels.CommandNameLabel);
            command.SetArg(PG.VDBParticleSystemToMeshLabels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(PG.VDBParticleSystemToMeshLabels.MeshIdLabel, meshId);
            command.SetArg(PG.VDBParticleSystemToMeshLabels.RadiusLabel, 5.0);
            return command.Execute(world.Adapter);
        }
    }
}
