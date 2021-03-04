using FluidStudio.Physics.Fluid;
using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Scene;
using System.Linq;
using CreateLabels = PG.FluidSceneCreateLabels;
using UpdateLabels = PG.FluidSceneUpdateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene : IPhysicsScene
    {
        public int Id { get; private set; }

        private int SourceParticleSystemId { get; set; }

        public string ParticleFilePath { get; private set; }

        public float ParticleRadius { get; private set; } = 0.5f;

        public int VolumeId { get; private set; }

        public string Name { get; private set; }

        public float Density { get; private set; } = 1.0f;

        public float Stiffness { get; private set; } = 1.0f;

        public float Viscosity { get; private set; } = 1.0f;

        public bool IsBoundary { get; private set; } = false;

        public FluidFileExportModel ExportModel { get; }
            = new FluidFileExportModel();

        public FluidScene()
        { }
        
        public void Create(SceneList world, VDBModel vdb, Canvas3d canvas, float particleRadius, float density, float stiffness, float viscosity, string name, bool isBoundary)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            this.VolumeId = vdb.CreateVDBVolume("Volume", false);
            canvas.BuildShader(world, VolumeId);

            Update(world, particleRadius, density, stiffness, viscosity, name, isBoundary);
        }

        public void Update(SceneList world, float particleRadius, float density, float stiffness, float viscosity, string name, bool isBoundary)
        {
            this.Name = name;
            this.ParticleRadius = particleRadius;
            this.Density = density;
            this.Stiffness = stiffness;
            this.Viscosity = viscosity;
            //this.SourceParticleSystemId = particleSystemId;
            this.IsBoundary = isBoundary;
            this.Name = name;
            Reset(world);
        }

        public void SetParticlesFromFile(VDBModel vdb, Canvas3d canvas, string particleFilePath, double particleRadius)
        {
            var ext = System.IO.Path.GetExtension(particleFilePath);
            if(ext == ".vdb")
            {
                SetParticlesFromVDBPoints(vdb, canvas, particleFilePath, particleRadius);
            }
            /*
            else if(ext == ".obj")
            {
                SetParticlesFromMesh(vdb, canvas, particleFilePath, particleRadius);
            }
            */
        }

        private void SetParticlesFromVDBPoints(VDBModel vdb, Canvas3d canvas, string particleFilePath, double particleRadius)
        {
            // TODO 前のPSのクリア処理．
            var ids = vdb.Read(particleFilePath, (float)particleRadius);
            if (ids.Count() > 0)
            {
                this.SourceParticleSystemId = ids[0];
                //canvas.BuildShader(world, this.SourceParticleSystemId);
                //canvas.Render();
                this.ParticleFilePath = particleFilePath;
            }
        }

        public void ExportFiles(SceneList world, VDBModel vdb, int timeStep)
        {
            ExportModel.ExportFiles(world, this, vdb, timeStep);
        }

        public void ConvertPSToVolume(SceneList world, VDBModel vdb, double radius)
        {
            vdb.ConvertPSToVolume(this.Id, this.VolumeId, radius);
        }

        public void Reset(SceneList world)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.ParticleSystemIdLabel, SourceParticleSystemId);
            command.SetArg(UpdateLabels.ParticleRadiusLabel, ParticleRadius);
            command.SetArg(UpdateLabels.DensityLabel, Density);
            command.SetArg(UpdateLabels.StiffnessLabel, Stiffness);
            command.SetArg(UpdateLabels.ViscosityLabel, Viscosity);
            command.SetArg(UpdateLabels.IsBoundary, IsBoundary);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(world.Adapter);
        }
    }
}
