using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class PhysicsSceneListViewModel
    {
        public ReactiveCollection<PhysicsSceneViewModel> Items { get; }
            = new ReactiveCollection<PhysicsSceneViewModel>();

        public PhysicsSceneListViewModel(IRegionManager regionManager, SceneList world)
        {
            Items.Add(new PhysicsSceneViewModel());
            /*
            this.world = world;
            this.regionManager = regionManager;
            Items = world.Scenes.ToReadOnlyReactiveCollection();
            */
        }

    }

}
