using Reactive.Bindings;
using Reactive.Bindings.Extensions;

namespace FluidStudio.Physics
{
    public class PhysicsSceneViewModel
    {
        public ReactiveCollection<PhysicsSceneViewModel> Children { get; }
            = new ReactiveCollection<PhysicsSceneViewModel>();

        public ReadOnlyReactiveProperty<string> Name { get; }

        public PhysicsSceneViewModel(PhysicsScene scene)
        {
            Name = scene.Name.ToReadOnlyReactiveProperty();
            foreach(var f in scene.Fluids)
            {
                Children.Add(new PhysicsSceneViewModel(f));
            }
            foreach(var b in scene.CSGBoundaries)
            {
                Children.Add(new PhysicsSceneViewModel(b));
            }
        }

        public PhysicsSceneViewModel(FluidScene scene)
        {
            Name = scene.Name.ToReadOnlyReactiveProperty();
        }

        public PhysicsSceneViewModel(CSGBoundaryScene scene)
        {
            Name = scene.Name.ToReadOnlyReactiveProperty();
        }
    }
}
