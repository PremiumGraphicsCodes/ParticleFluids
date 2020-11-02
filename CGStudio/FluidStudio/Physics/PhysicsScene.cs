using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics
{
    public class PhysicsScene
    {
        public ReactiveCollection<FluidScene> Fluids { get; }
            = new ReactiveCollection<FluidScene>();
    }

}
