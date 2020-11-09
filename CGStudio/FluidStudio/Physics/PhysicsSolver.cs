using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;

namespace FluidStudio.Physics
{
    public class PhysicsSolver
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("PhysicsScene01");

        public ReactiveCollection<FluidScene> Fluids { get; }
            = new ReactiveCollection<FluidScene>();

        public ReactiveCollection<CSGBoundaryScene> CSGBoundaries { get; }
            = new ReactiveCollection<CSGBoundaryScene>();

        public ReactiveProperty<float> TimeStep { get; }
            = new ReactiveProperty<float>(0.03f);

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
            command.SetArg(Labels.TimeStepLabel, TimeStep.Value);
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
