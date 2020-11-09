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

        public void ChangeView(PhysicsSceneViewModel selectedItem)
        {
            if (selectedItem == null)
            {
                return;
            }
            var type = selectedItem.SceneType;
            var parameters = new NavigationParameters();
            switch (type)
            {
                case PhysicsSceneType.Solver:
                    NavigateView("PhysicsSceneEdit", parameters);
                    break;
                case PhysicsSceneType.Fluid:
                    parameters.Add("FluidSceneEdit", selectedItem);
                    NavigateView("FluidSceneEdit", parameters);
                    break;
                case PhysicsSceneType.CSGBoundary:
                    parameters.Add("CSGBoundarySceneEdit", selectedItem);
                    NavigateView("CSGBoundarySceneEdit", parameters);
                    break;
                default:
                    break;
            }
        }
    }
}
