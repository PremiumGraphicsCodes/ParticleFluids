using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class PhysicsSceneViewModel
    {
        public ReadOnlyReactiveCollection<PhysicsSceneViewModel> Children { get; }

        public ReadOnlyReactiveProperty<string> Name { get; }

        public PhysicsSceneViewModel(PhysicsScene scene)
        {
            Name = scene.Name.ToReadOnlyReactiveProperty();
            Children = scene.Fluids.ToReadOnlyReactiveCollection(x => new PhysicsSceneViewModel(x));
        }

        public PhysicsSceneViewModel(FluidScene scene)
        {
            Name = scene.Name.ToReadOnlyReactiveProperty();
        }
    }
}
