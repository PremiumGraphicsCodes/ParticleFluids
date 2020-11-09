using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using Labels = PG.FluidSceneCreateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene
    {
        private int id;
        public int Id { get { return id; } }

        private int particleSystemId;
        public int ParticleSystemId { get { return particleSystemId; } }

        private string name;
        public string Name { get { return name; } }

        public ReactiveProperty<float> Stiffness { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Viscosity { get; }
            = new ReactiveProperty<float>(1.0f);

        public FluidScene(SceneList world, int particleSystemId, float stiffness, float viscosity)
        {
            Create(world, particleSystemId, stiffness, viscosity);
        }

        public void Create(SceneList world, int particleSystemId, float stiffness, float viscosity)
        {
            this.Stiffness.Value = stiffness;
            this.Viscosity.Value = viscosity;
            this.particleSystemId = particleSystemId;
            var command = new PG.CLI.PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(Labels.StiffnessLabel, stiffness);
            command.SetArg(Labels.ViscosityLabel, viscosity);
            command.SetArg(Labels.NameLabel, "NewFluid");
            command.Execute(world.Adapter);
            this.id = command.GetResult<int>(Labels.NewIdLabel);
        }

        public void SendShader(SceneList world, Canvas3d canvas)
        {
            canvas.SendShader(world, id);
            canvas.Render();
        }
    }
}
