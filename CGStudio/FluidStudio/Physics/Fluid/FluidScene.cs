using PG.Control.OpenGL;
using PG.Scene;
using CreateLabels = PG.FluidSceneCreateLabels;
using UpdateLabels = PG.FluidSceneUpdateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene : IPhysicsScene
    {
        public int Id { get; private set; }

        public int ParticleSystemId { get; private set; }

        public string Name { get; private set; }

        public float Stiffness { get; private set; } = 1.0f;

        public float Viscosity { get; private set; } = 1.0f;

        public FluidScene(SceneList world, int particleSystemId, float stiffness, float viscosity, string name)
        {
            Create(world, particleSystemId, stiffness, viscosity, name);
        }

        public void Create(SceneList world, int particleSystemId, float stiffness, float viscosity, string name)
        {
            var command = new PG.CLI.PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            Update(world, particleSystemId, stiffness, viscosity, name);
        }

        public void Update(SceneList world, int particleSystemId, float stiffness, float viscosity, string name)
        {
            this.Name = name;
            this.Stiffness = stiffness;
            this.Viscosity = viscosity;
            this.ParticleSystemId = particleSystemId;
            this.Name = name;
            Reset(world);
        }

        public void Reset(SceneList world)
        {
            var command = new PG.CLI.PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.ParticleSystemIdLabel, ParticleSystemId);
            command.SetArg(UpdateLabels.StiffnessLabel, Stiffness);
            command.SetArg(UpdateLabels.ViscosityLabel, Viscosity);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(world.Adapter);

        }
    }
}
