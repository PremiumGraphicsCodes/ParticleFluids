using PG.CLI;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics
{

    public class PhysicsSceneList
    {
        public ReactiveCollection<PhysicsScene> Scenes { get; }
            = new ReactiveCollection<PhysicsScene>();

        public PhysicsSceneList()
        {
            this.Scenes.Add(new PhysicsScene());
        }
    }
}
