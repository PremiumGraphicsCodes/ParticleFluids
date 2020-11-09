using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;

namespace FluidStudio.Physics
{
    public class PhysicsSceneListViewModel
    {
        public ReadOnlyReactiveCollection<PhysicsSceneViewModel> Items { get; }

        private readonly IRegionManager regionManager;

        public PhysicsSceneListViewModel(IRegionManager regionManager, SceneList world, MainModel mainModel)
        {
            this.regionManager = regionManager;
            this.Items = mainModel.PhysicsModel.Scenes.ToReadOnlyReactiveCollection(x => new PhysicsSceneViewModel(x));
        }

        private void NavigateView(string name, NavigationParameters navigationParameters)
        {
            regionManager.RequestNavigate("ContentRegion", name, navigationParameters);
        }

        public void ChangeView(IPhysicsScene selectedItem)
        {
            if (selectedItem == null)
            {
                return;
            }
            var parameters = new NavigationParameters();
            parameters.Add("Scene", selectedItem);
            if(selectedItem is CSGBoundaryScene)
            {
                NavigateView("CSGBoundaryGeneration", parameters);
            }
            else if(selectedItem is FluidScene)
            {
                NavigateView("FluidGeneration", parameters);
            }
        }
    }
}
