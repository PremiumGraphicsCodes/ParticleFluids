using PG.Control.OpenGL;
using PG.Scene;
using System.Collections.Generic;

namespace FluidStudio.VDB
{
    public class VDBModel
    {
        public void Init(SceneList world)
        {
            var command = new PG.CLI.OpenVDBCommand(PG.VDBInitLabels.CommandNameLabel);
            command.Execute(world.Adapter);
        }

        public bool Read(string filePath, SceneList world, Canvas3d canvas)
        {
            var command = new PG.CLI.OpenVDBCommand(PG.VDBFileReadLabels.CommandNameLabel);
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

        public bool Write(string filePath, SceneList world,int particleSystemId)
        {
            var command = new PG.CLI.OpenVDBCommand(PG.VDBFileWriteLabels.CommandNameLabel);
            command.SetArg(PG.VDBFileWriteLabels.FilePathLabel, filePath);
            command.SetArg(PG.VDBFileWriteLabels.ParticleSystemIdLabel, particleSystemId);
            if (!command.Execute(world.Adapter))
            {
                return false;
            }
            return true;
        }
    }
}
