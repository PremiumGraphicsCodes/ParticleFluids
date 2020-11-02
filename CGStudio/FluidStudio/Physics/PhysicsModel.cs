using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics
{

    public class PhysicsModel
    {
        public ReactiveCollection<PhysicsScene> Scenes { get; }
            = new ReactiveCollection<PhysicsScene>();

        public PhysicsModel()
        {
            this.Scenes.Add(new PhysicsScene());
        }

        public void Simulate(float timeStep)
        {
            foreach(var scene in Scenes)
            {
                
            }
        }
    }
}
