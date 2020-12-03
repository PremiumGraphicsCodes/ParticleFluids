using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;
using CreateLabels = PG.PhysicsSolverCreateLabels;
using UpdateLabels = PG.PhysicsSolverUpdateLabels;
using FluidStudio.VDB;

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
            this.Fluids = fluids;
            this.CSGBoundaries = boundaries;
            this.TimeStep = timeStep;
            this.Name = name;
            Reset(world);
        }

        public void Simulate(SceneList scenes)
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.SolverIdLabel, Id);
            command.Execute(scenes.Adapter);

            /*
            var destIds = new List<int>();
            foreach(var fluid in Fluids)
            {
                var fluidId = fluid.Id;
                var destId = fluid.DestPartcileSystemId;
                if (destId > 0)
                {
                    command.Create(PG.FluidSceneToPSLabels.CommandNameLabel);
                    command.SetArg(PG.FluidSceneToPSLabels.FluidIdLabel, fluidId);
                    command.SetArg(PG.FluidSceneToPSLabels.ParticleSystemIdLabel, destId);
                    command.Execute(scenes.Adapter);
                    canvas.SendShader(scenes, destId);
                    var ids = new List<int>();
                    destIds.Add(destId);
                }
            }
            vdb.Write("Test.vdb", scenes, destIds);
            */
        }

        public void Reset(SceneList world)
        {
            var fluidIds = new List<int>();
            foreach (var f in Fluids)
            {
                fluidIds.Add(f.Id);
            }
            var boundaryIds = new List<int>();
            foreach (var b in CSGBoundaries)
            {
                boundaryIds.Add(b.Id);
            }


            var command = new PhysicsCommand(UpdateLabels.CommandNameLabel);
            command.SetArg(UpdateLabels.IdLabel, Id);
            command.SetArg(UpdateLabels.FluidSceneIdsLabel, fluidIds);
            command.SetArg(UpdateLabels.CSGBoundarySceneIdsLabel, boundaryIds);
            command.SetArg(UpdateLabels.TimeStepLabel, TimeStep);
            command.SetArg(UpdateLabels.NameLabel, Name);
            command.Execute(world.Adapter);
        }
    }
}
