using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class PhysicsSceneListViewModel
    {
        public ReadOnlyReactiveCollection<PhysicsSceneViewModel> Items { get; }

        public PhysicsSceneListViewModel(IRegionManager regionManager, SceneList world, MainModel mainModel)
        {
            Items = mainModel.PhysicsModel.Scenes.ToReadOnlyReactiveCollection(x => new PhysicsSceneViewModel(x));
            /*
            Items.Add(new PhysicsSceneViewModel());
            this.world = world;
            this.regionManager = regionManager;
            Items = world.Scenes.ToReadOnlyReactiveCollection();
            */
        }

    }

}
