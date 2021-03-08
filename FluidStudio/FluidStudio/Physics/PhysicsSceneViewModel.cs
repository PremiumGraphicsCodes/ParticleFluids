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
        public ReadOnlyReactiveCollection<PhysicsSceneViewModel> Children { get; }

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

            this.Children = scene.Children.ToReadOnlyReactiveCollection(x => new PhysicsSceneViewModel(x));
        }

        public PhysicsSceneViewModel(IPhysicsScene scene)
        {
            this.Model = scene;
            if (scene is FluidScene)
            {
                this.SceneType = PhysicsSceneType.Fluid;
            }
            else if(scene is CSGBoundaryScene)
            {
                this.SceneType = PhysicsSceneType.CSGBoundary;
            }
            this.Id.Value = scene.Id;
            Name.Value = scene.Name;
        }

        /*
        public PhysicsSceneViewModel(CSGBoundaryScene scene)
        {
            this.Model = scene;
            this.SceneType = PhysicsSceneType.CSGBoundary;
            this.Id.Value = scene.Id;
            Name.Value = scene.Name;
        }
        */
    }
}
