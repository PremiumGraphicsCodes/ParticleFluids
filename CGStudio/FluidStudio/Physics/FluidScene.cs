using PG.Scene;
using Reactive.Bindings;
using Labels = PG.FluidSceneCreateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene
    {
        private int id;
        public int Id { get { return id; } }

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Fluid01");

//        private int particleSystemId;
//        public int ParticleSystemId { get; }

        public FluidScene(SceneList world, int particleSystemId, float stiffness, float viscosity)
        {
            Create(world, particleSystemId, stiffness, viscosity);
        }

        public void Create(SceneList world, int particleSystemId, float stiffness, float viscosity)
        {
            var command = new PG.CLI.PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(Labels.StiffnessLabel, stiffness);
            command.SetArg(Labels.ViscosityLabel, viscosity);
            command.SetArg(Labels.NameLabel, "NewFluid");
            command.Execute(world.Adapter);
            this.id = command.GetResult<int>(Labels.NewIdLabel);
        }
    }
}
