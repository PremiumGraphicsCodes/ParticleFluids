using Reactive.Bindings;
using Reactive.Bindings.ObjectExtensions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics
{
    public class PhysicsSceneViewModel
    {
        public ReactiveProperty<PhysicsSceneViewModel> Children { get; }
            = new ReactiveProperty<PhysicsSceneViewModel>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();
        public ReactiveCollection<int> Ids { get; }
            = new ReactiveCollection<int>();

        public PhysicsSceneViewModel()
        {
            Name.Value = "Name";
            Ids.Add(1);
        }
    }
}
