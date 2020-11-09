using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;

namespace FluidStudio.Physics
{
    public class SolverScene
    {
        public string Name { get; private set; } = "Solver01";

        public List<FluidScene> Fluids { get; }
            = new List<FluidScene>();

        public List<CSGBoundaryScene> CSGBoundaries { get; }
            = new List<CSGBoundaryScene>();

        public float TimeStep { get; private set; } = 0.03f;

        public void Simulate(SceneList scenes)
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            var ids = new List<int>();
            foreach (var scene in Fluids)
            {
                ids.Add(scene.Id);
            }
            var boundaryIds = new List<int>();
            foreach(var b in CSGBoundaries)
            {
                boundaryIds.Add(b.Id);
            }
            command.SetArg(Labels.FluidSceneIdsLabel, ids);
            command.SetArg(Labels.CSGBoundarySceneIdsLabel, boundaryIds);
            command.SetArg(Labels.TimeStepLabel, TimeStep);
            command.Execute(scenes.Adapter);
        }

        public void SendShader(SceneList scenes, Canvas3d canvas)
        {
            foreach (var scene in Fluids)
            {
                scene.SendShader(scenes, canvas);
            }
        }

    }

}
