using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;

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
            var command = new PhysicsCommand(CreateLabels.CommandNameLabel);
            command.Execute(scenes.Adapter);
            this.Id = command.GetResult<int>(CreateLabels.NewIdLabel);
            Update(scenes, fluids, boundaries, timeStep, name);
        }

        public void Update(SceneList world, List<FluidScene> fluids, List<CSGBoundaryScene> boundaries, float timeStep, string name)
        {
            var fluidIds = new List<int>();
            foreach (var f in fluids)
            {
                fluidIds.Add(f.Id);
            }
            this.Fluids = fluids;
            var boundaryIds = new List<int>();
            foreach (var b in boundaries)
            {
                boundaryIds.Add(b.Id);
            }
            this.CSGBoundaries = boundaries;

            var command = new PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.FluidSceneIdsLabel, fluidIds);
            command.SetArg(UpdateLabels.CSGBoundarySceneIdsLabel, boundaryIds);
            command.SetArg(UpdateLabels.TimeStepLabel, timeStep);
            command.SetArg(UpdateLabels.NameLabel, name);
            command.Execute(world.Adapter);
        }

        public void Simulate(SceneList scenes)
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.SolverIdLabel, Id);
            command.Execute(scenes.Adapter);
        }
    }
}
