using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;

namespace FluidStudio.Physics
{
    public class SolverScene : IPhysicsScene
    {
        public string Name { get; private set; } = "Solver01";

        public List<FluidScene> Fluids { get; private set; }
            = new List<FluidScene>();

        public List<CSGBoundaryScene> CSGBoundaries { get; private set; }
            = new List<CSGBoundaryScene>();

        public float TimeStep { get; private set; } = 0.03f;

        public int Id { get; private set; }

        public void Create(SceneList scenes, List<FluidScene> fluids, List<CSGBoundaryScene> boundaries, float timeStep, string name)
        {
            var fluidIds = new List<int>();
            foreach(var f in fluids)
            {
                fluidIds.Add(f.Id);
            }
            this.Fluids = fluids;
            var boundaryIds = new List<int>();
            foreach(var b in boundaries)
            {
                boundaryIds.Add(b.Id);
            }
            var command = new PhysicsCommand(CreateLabels.CommandNameLabel);
            command.SetArg(CreateLabels.FluidSceneIdsLabel, fluidIds);
            command.SetArg(CreateLabels.CSGBoundarySceneIdsLabel, boundaryIds);
            command.SetArg(CreateLabels.TimeStepLabel, timeStep);
            command.SetArg(CreateLabels.NameLabel, name);
            command.Execute(scenes.Adapter);
        }

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
