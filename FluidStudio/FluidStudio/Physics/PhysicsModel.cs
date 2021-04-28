using FluidStudio.VDB;
using PG.CLI;
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
                solver.Simulate();
                foreach (var fluid in solver.Fluids)
                {
                    canvas.SendShader(world, fluid.Id);
                }
                foreach(var emitter in solver.Emitters)
                {
                    canvas.SendShader(world, emitter.Id);
                }
                foreach (var fluid in solver.Fluids)
                {
                    fluid.ExportFiles(vdb, TimeStep.Value);
                }
                foreach(var emitter in solver.Emitters)
                {
                    emitter.ExportFiles(vdb, TimeStep.Value);
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
                    fluid.Send();
                    canvas.SendShader(world, fluid.Id);
                }
                ps.Send();
                canvas.Render();
            }
            TimeStep.Value = 0;
        }

        public void ToSmoothVolume(SceneList world, int particleSystemId, int sparseVolumeId, float effectLength, float cellLength)
        {
            var command = new PhysicsCommand(PG.SPHSurfaceConstructionLabels.CommandNameLabel);
            command.SetArg(PG.SPHSurfaceConstructionLabels.ParticleSystemIdLabel, particleSystemId);
            command.SetArg(PG.SPHSurfaceConstructionLabels.SparseVolumeIdLabel, sparseVolumeId);
            command.SetArg(PG.SPHSurfaceConstructionLabels.EffectLengthLabel, effectLength);
            command.SetArg(PG.SPHSurfaceConstructionLabels.CellLengthLabel, cellLength);
            command.Execute(world.Adapter);
        }
    }
}
