using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class PhysicsSceneViewModel
    {
        public ReactiveProperty<PhysicsSceneViewModel> Children { get; }
            = new ReactiveProperty<PhysicsSceneViewModel>();

        public ReadOnlyReactiveProperty<string> Name { get; }
        public ReactiveCollection<int> Ids { get; }
            = new ReactiveCollection<int>();

        public PhysicsSceneViewModel(PhysicsScene scene)
        {
            Name = scene.Name.ToReadOnlyReactiveProperty();
            Ids.Add(1);
        }
    }
}
