using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics
{
    class BoundaryScene
    {

    }

    class PhysicsScene
    {
        public ReactiveProperty<FluidScene> Fluids { get; }
            = new ReactiveProperty<FluidScene>();

        public ReactiveProperty<BoundaryScene> Boundaries { get; }
            = new ReactiveProperty<BoundaryScene>();
    }

    class PhysicsModel
    {
        public ReactiveProperty<PhysicsScene> Scenes { get; }
            = new ReactiveProperty<PhysicsScene>(); 
    }
}
