using PG.Control.OpenGL;
using PG.Scene;
using CreateLabels = PG.FluidSceneCreateLabels;
using UpdateLabels = PG.FluidSceneUpdateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene : IPhysicsScene
    {
        public int Id { get; private set; }

        public int SourceParticleSystemId { get; private set; }

        public int PolygonMeshId { get; set; }

        public string Name { get; private set; }

        public float Stiffness { get; private set; } = 1.0f;

        public float Viscosity { get; private set; } = 1.0f;

        public bool IsBoundary { get; private set; } = false;

        public FluidScene()
        { }
        
        public void Create(SceneList world, int particleSystemId, float stiffness, float viscosity, string name, bool isBoundary)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            Update(world, particleSystemId, stiffness, viscosity, name, isBoundary);
        }

        public void Update(SceneList world, int particleSystemId, float stiffness, float viscosity, string name, bool isBoundary)
        {
            this.Name = name;
            this.Stiffness = stiffness;
            this.Viscosity = viscosity;
            this.SourceParticleSystemId = particleSystemId;
            this.IsBoundary = isBoundary;
            this.Name = name;
            Reset(world);
        }

        public void Reset(SceneList world)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.ParticleSystemIdLabel, SourceParticleSystemId);
            command.SetArg(UpdateLabels.StiffnessLabel, Stiffness);
            command.SetArg(UpdateLabels.ViscosityLabel, Viscosity);
            command.SetArg(UpdateLabels.IsBoundary, IsBoundary);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(world.Adapter);
        }
    }
}
