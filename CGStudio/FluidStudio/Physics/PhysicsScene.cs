using PG.CLI;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using Labels = PG.FluidSimulationLabels;

namespace FluidStudio.Physics
{
    public class PhysicsScene
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("PhysicsScene01");

        public ReactiveCollection<FluidScene> Fluids { get; }
            = new ReactiveCollection<FluidScene>();

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
            command.SetArg(Labels.FluidSceneIdsLabel, ids);
            command.SetArg(Labels.TimeStepLabel, TimeStep.Value);
            command.Execute(scenes.Adapter);
        }

    }

}
