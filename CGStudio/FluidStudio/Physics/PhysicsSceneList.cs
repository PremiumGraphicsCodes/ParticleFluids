using Reactive.Bindings;

namespace FluidStudio.Physics
{

    public class PhysicsSceneList
    {
        public ReactiveCollection<PhysicsSolver> Scenes { get; }
            = new ReactiveCollection<PhysicsSolver>();

        public PhysicsSceneList()
        {
//            this.Scenes.Add(new PhysicsScene());
        }
    }
}
