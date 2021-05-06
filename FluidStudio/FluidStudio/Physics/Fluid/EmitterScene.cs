using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using System.Linq;
using CreateLabels = PG.EmitterSceneCreateLabels;
using UpdateLabels = PG.EmitterSceneUpdateLabels;


namespace FluidStudio.Physics.Fluid
{
    public class EmitterScene : IPhysicsScene
    {
        public int Id { get; private set; }

        private int SourceParticleSystemId { get; set; }

        public string ParticleFilePath { get; private set; }

        public float ParticleRadius { get; set; } = 0.5f;

        public int VolumeId { get; private set; }

        public string Name { get; set; }

        public float Density { get; set; } = 1000.0f;

        public float Stiffness { get; set; } = 1.0f;

        public Vector3d InitialVelocity { get; set; } = new Vector3d(0, 0, 0);

        public float Viscosity { get; set; } = 1.0f;

        public int StartTimeStep { get; set; } = 0;

        public int EndTimeStep { get; set; } = 100;

        public int Interval { get; set; } = 10;

        public FluidFileExportModel ExportModel { get; }
            = new FluidFileExportModel();

        public IPhysicsScene Parent { get; private set; }

        private readonly SceneList scenes;

        public EmitterScene(SceneList scenes, SolverScene parent, VDBModel vdb, Canvas3d canvas)
        {
            this.scenes = scenes;
            this.Parent = parent;
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.VolumeId = vdb.CreateVDBVolume("Volume", false);
            canvas.BuildShader(scenes, VolumeId);
        }

        public void SetParticlesFromFile(VDBModel vdb, FileIOModel ioModel, Canvas3d canvas, string particleFilePath, double particleRadius)
        {
            var ext = System.IO.Path.GetExtension(particleFilePath);
            if (ext != ".vdb")
            {
                return;
            }
            var absolutePath = ioModel.ToFullPath(particleFilePath);
            // TODO 前のPSのクリア処理．
            var ids = vdb.Read(absolutePath, (float)particleRadius);
            if (ids.Count() > 0)
            {
                this.SourceParticleSystemId = ids[0];
                this.ParticleFilePath = particleFilePath;
            }
        }

        public void ExportFiles(VDBModel vdb, int timeStep)
        {
            //ExportModel.ExportFiles(scenes, this, vdb, timeStep);
        }

        public void ConvertPSToVolume(VDBModel vdb, double radius)
        {
            vdb.ConvertPSToVolume(this.Id, this.VolumeId, radius);
        }

        public void Send()
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.ParticleSystemIdLabel, SourceParticleSystemId);
            command.SetArg(UpdateLabels.ParticleRadiusLabel, ParticleRadius);
            command.SetArg(UpdateLabels.DensityLabel, Density);
            command.SetArg(UpdateLabels.StiffnessLabel, Stiffness);
            command.SetArg(UpdateLabels.ViscosityLabel, Viscosity);
            command.SetArg(UpdateLabels.InitialVelocityLabel, InitialVelocity);
            //command.SetArg(UpdateLabels.IsBoundary, IsBoundary);
            command.SetArg(UpdateLabels.StartStepLabel, StartTimeStep);
            command.SetArg(UpdateLabels.EndStepLabel, EndTimeStep);
            command.SetArg(UpdateLabels.IntervalLabel, Interval);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(scenes.Adapter);
        }

        public void Delete()
        {
            scenes.Delete(SourceParticleSystemId);
            scenes.Delete(Id);
            scenes.Delete(VolumeId);
        }

    }
}
