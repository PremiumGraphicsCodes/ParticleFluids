using Reactive.Bindings;

namespace FluidStudio.Physics
{
    // enum でタイプを定義する．

    public enum PhysicsSceneType
    {
        Solver,
        Fluid,
        CSGBoundary,
        MeshBoundary,
    };

    public class PhysicsSceneViewModel
    {
        public ReactiveCollection<PhysicsSceneViewModel> Children { get; }
            = new ReactiveCollection<PhysicsSceneViewModel>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public PhysicsSceneType SceneType { get; }

        public IPhysicsScene Model { get; private set; }

        public PhysicsSceneViewModel(SolverScene scene)
        {
            this.SceneType = PhysicsSceneType.Solver;
            this.Model = scene;
            Name.Value = scene.Name;
//            Id = scene.Id
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
            this.Model = scene;
            this.SceneType = PhysicsSceneType.Fluid;
            this.Id.Value = scene.Id;
            Name.Value = scene.Name;
        }

        public PhysicsSceneViewModel(CSGBoundaryScene scene)
        {
            this.Model = scene;
            this.SceneType = PhysicsSceneType.CSGBoundary;
            this.Id.Value = scene.Id;
            Name.Value = scene.Name;
        }
    }
}
