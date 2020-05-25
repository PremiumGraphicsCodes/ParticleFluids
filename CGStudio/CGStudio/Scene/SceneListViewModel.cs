using Reactive.Bindings;
using PG.Scene;
using Prism.Regions;
using Prism.Mvvm;

namespace PG.CGStudio
{
    public class SceneListViewModel : BindableBase
    {
        public ReadOnlyReactiveCollection<SceneModel> Items { get; }

        private readonly IRegionManager regionManager;

        public SceneListViewModel(IRegionManager regionManager, World world)
        {
            this.regionManager = regionManager;
            Items = world.Scenes.Scenes.ToReadOnlyReactiveCollection();
        }

        public void NavigateView(string name, NavigationParameters navigationParameters)
        {
            regionManager.RequestNavigate("ContentRegion", name, navigationParameters);
        }
    }
}
