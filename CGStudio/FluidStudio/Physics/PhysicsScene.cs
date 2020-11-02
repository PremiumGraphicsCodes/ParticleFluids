using PG.CLI;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Labels = PG.FluidSimulationLabels;

namespace FluidStudio.Physics
{
    public class PhysicsScene
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("PhysicsScene01");

        public ReactiveCollection<FluidScene> Fluids { get; }
            = new ReactiveCollection<FluidScene>();

        public void Simulate(float timeStep)
        {
            var command = new PhysicsCommand(Labels.CommandNameLabel);
            var ids = new List<int>();
            foreach (var scene in Fluids)
            {
                //                ids.Add(scene.)
            }
            command.SetArg(Labels.FluidSceneIdsLabel, ids);

        }

    }

}
