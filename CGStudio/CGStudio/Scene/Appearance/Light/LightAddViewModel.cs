using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Appearance.Light
{
    public class LightAddViewModel : BindableBase, INavigationAware
    {
        public PointLightViewModel PointLightViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public LightAddViewModel()
        {
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
        }


        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {

        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["LightAdd"] as PG.Core.Scene;
            if (item == null)
            {
                return;
            }
            //var light = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindLightById(item.Id);
            //this.PointLightViewModel.Value = light;
        }
    }
}