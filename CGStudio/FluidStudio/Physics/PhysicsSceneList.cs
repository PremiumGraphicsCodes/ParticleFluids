using Reactive.Bindings;

namespace FluidStudio.Physics
{

    public class PhysicsSceneList
    {
        public ReactiveCollection<SolverScene> Scenes { get; }
            = new ReactiveCollection<SolverScene>();

        public PhysicsSceneList()
        {
//            this.Scenes.Add(new PhysicsScene());
        }
    }
}
