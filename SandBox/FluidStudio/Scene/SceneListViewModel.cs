using FluidStudio.Scene.VDB;
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

        private void NavigateView(string name, NavigationParameters navigationParameters)
        {
            regionManager.RequestNavigate("ContentRegion", name, navigationParameters);
        }

        public void ChangeView(VDBSceneModel selectedItem)
        {
            /*
            if (selectedItem == null)
            {
                return;
            }
            var parameters = new NavigationParameters();
            parameters.Add("Scene", selectedItem);
            if (selectedItem is SolverScene)
            {
                NavigateView("SolverUpdate", parameters);
            }
            else if (selectedItem is FluidScene)
            {
                NavigateView("FluidUpdate", parameters);
            }
            else if (selectedItem is CSGBoundaryScene)
            {
                NavigateView("CSGBoundaryUpdate", parameters);
            }
            */
        }
    }
}
