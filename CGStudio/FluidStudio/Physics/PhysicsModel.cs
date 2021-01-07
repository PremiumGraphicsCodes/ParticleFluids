using FluidStudio.VDB;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;

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

        public void Simulate(SceneList world, Canvas3d canvas)
        {
            foreach (var ps in Solvers)
            {
                ps.Simulate(world);
                foreach (var fluid in ps.Fluids)
                {
                    canvas.SendShader(world, fluid.Id);
                }
                canvas.Render();
            }
            TimeStep.Value++;
        }

        public void ExportVDB(SceneList world, VDBModel vdb, string directoryPath)
        {
            foreach (var solver in Solvers)
            {
                var filePath = directoryPath + "/" + solver.Name + "_" + TimeStep.Value.ToString() + ".vdb";
                solver.ExportVDB(world, vdb, filePath);
            }
        }

        public void ConvertToMesh(SceneList world, VDBModel vdb, Canvas3d canvas)
        {
            foreach (var ps in Solvers)
            {
                foreach (var fluid in ps.Fluids)
                {
                    vdb.BuildMesh(fluid.SourceParticleSystemId, fluid.PolygonMeshId, world);
                    canvas.SendShader(world, fluid.PolygonMeshId);
                }
                canvas.Render();
            }
        }

        public void ExportMesh(SceneList world, VDBModel vdb, string directoryPath)
        {
            foreach (var solver in Solvers)
            {
                foreach (var fluid in solver.Fluids)
                {
                    var filePath = directoryPath + "/" + solver.Name + "_"  + fluid.Name + "_" + TimeStep.Value.ToString() + ".obj";
                    vdb.WriteOBJ(world, fluid.PolygonMeshId, filePath);
                }
            }
        }

        public void Reset(SceneList world, Canvas3d canvas)
        {
            foreach (var ps in Solvers)
            {
                ps.Reset(world);
                foreach (var fluid in ps.Fluids)
                {
                    fluid.Reset(world);
                    canvas.SendShader(world, fluid.Id);
                }
                canvas.Render();
            }
            TimeStep.Value = 0;
        }
    }
}
