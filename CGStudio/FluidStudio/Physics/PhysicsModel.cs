using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class PhysicsModel
    {
        public ReactiveCollection<SolverScene> Scenes { get; }
            = new ReactiveCollection<SolverScene>();

        public PhysicsModel()
        {
//            this.Scenes.Add(new PhysicsScene());
        }

        public void Simulate(SceneList world, Canvas3d canvas)
        {
            foreach (var ps in Scenes)
            {
                ps.Simulate(world);
                foreach (var fluid in ps.Fluids)
                {
                    canvas.SendShader(world, fluid.Id);
                }
                canvas.Render();
            }
        }
    }
}
