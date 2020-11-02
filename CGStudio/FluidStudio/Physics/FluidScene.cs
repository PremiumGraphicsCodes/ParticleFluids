using PG.Scene;
using Labels = PG.FluidSceneCreateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene
    {
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
            var newId = command.GetResult<int>(Labels.NewIdLabel);
        }
    }
}
