using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Linq;

namespace FluidStudio.Physics
{
    public class PhysicsModel
    {
        public ReactiveCollection<SolverScene> Solvers { get; }
            = new ReactiveCollection<SolverScene>();

        public ReactiveProperty<int> TimeStep { get; }
            = new ReactiveProperty<int>(0);

        public PhysicsModel()
        {
            //            this.Scenes.Add(new PhysicsScene());
        }

        public void Clear()
        {
            foreach(var solver in Solvers)
            {
                solver.Clear();
            }
            var root = Solvers.FirstOrDefault();
            Solvers.Clear();
            Solvers.Add(root);
        }

        public void Simulate(SceneList world, VDBModel vdb, Canvas3d canvas)
        {
            foreach (var solver in Solvers)
            {
                solver.Simulate(vdb, TimeStep.Value);
                foreach (var fluid in solver.Fluids)
                {
                    canvas.SendShader(world, fluid.Id);
                }
                foreach (var fluid in solver.Fluids)
                {
                    fluid.ExportFiles(world, vdb, TimeStep.Value);
                }
                canvas.Render();
            }
            TimeStep.Value++;
        }

        public void Reset(SceneList world, FileIOModel ioModel, VDBModel vdb, Canvas3d canvas)
        {
            foreach (var ps in Solvers)
            {
                foreach (var fluid in ps.Fluids)
                {
                    fluid.SetParticlesFromFile(vdb, ioModel, canvas, fluid.ParticleFilePath, fluid.ParticleRadius);
                    fluid.Reset(world);
                    canvas.SendShader(world, fluid.Id);
                }
                ps.Reset();
                canvas.Render();
            }
            TimeStep.Value = 0;
        }
    }
}
