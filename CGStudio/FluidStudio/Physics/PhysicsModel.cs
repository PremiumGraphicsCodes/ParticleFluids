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

        public void Simulate(SceneList world, VDBModel vdb, Canvas3d canvas)
        {
            foreach (var solver in Solvers)
            {
                solver.Simulate(world, vdb, TimeStep.Value);
                foreach (var fluid in solver.Fluids)
                {
                    canvas.SendShader(world, fluid.Id);
                }
                foreach (var fluid in solver.Fluids)
                {
//                    fluid.ExportFiles();
                    //ExportModel.ExportFiles(scenes, fluid, vdb, timeStep);
                }
                canvas.Render();
            }
            TimeStep.Value++;
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
