using Reactive.Bindings;

namespace FluidStudio.Physics
{

    public class PhysicsSceneList
    {
        public ReactiveCollection<PhysicsScene> Scenes { get; }
            = new ReactiveCollection<PhysicsScene>();

        public PhysicsSceneList()
        {
//            this.Scenes.Add(new PhysicsScene());
        }
    }
}
