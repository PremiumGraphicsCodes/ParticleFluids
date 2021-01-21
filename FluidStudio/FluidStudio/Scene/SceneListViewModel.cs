using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;

namespace FluidStudio.Scene
{
    public class SceneListViewModel
    {
        public ReadOnlyReactiveCollection<SceneModel> Items { get; }

        private readonly IRegionManager regionManager;

        private readonly SceneList world;

        public SceneListViewModel(IRegionManager regionManager, SceneList world)
        {
            this.world = world;
            this.regionManager = regionManager;
            Items = world.Scenes.ToReadOnlyReactiveCollection();
        }
    }
}
