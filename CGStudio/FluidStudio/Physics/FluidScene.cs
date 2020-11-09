using PG.Control.OpenGL;
using PG.Scene;
using Labels = PG.FluidSceneCreateLabels;

namespace FluidStudio.Physics
{
    public class FluidScene
    {
        public int Id { get; private set; }

        private int particleSystemId;
        public int ParticleSystemId { get { return particleSystemId; } }

        public string Name { get; private set; }

        public float Stiffness { get; private set; } = 1.0f;

        public float Viscosity { get; private set; } = 1.0f;

        public FluidScene(SceneList world, int particleSystemId, float stiffness, float viscosity)
        {
            Create(world, particleSystemId, stiffness, viscosity);
        }

        public void Create(SceneList world, int particleSystemId, float stiffness, float viscosity)
        {
            this.Stiffness = stiffness;
            this.Viscosity = viscosity;
            this.particleSystemId = particleSystemId;
            var command = new PG.CLI.PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(Labels.StiffnessLabel, stiffness);
            command.SetArg(Labels.ViscosityLabel, viscosity);
            command.SetArg(Labels.NameLabel, "NewFluid");
            command.Execute(world.Adapter);
            this.Id = command.GetResult<int>(Labels.NewIdLabel);
        }

        public void SendShader(SceneList world, Canvas3d canvas)
        {
            canvas.SendShader(world, Id);
            canvas.Render();
        }
    }
}
