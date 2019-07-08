using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Light
{
    public class LightEditViewModel : BindableBase, INavigationAware
    {
        //private PG.Core.Graphics.PointLight PrevLight;

        public PointLightViewModel PointLightViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public LightEditViewModel()
        {
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            //this.PointLightViewModel.Update(this.PrevLight);
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
            var item = navigationContext.Parameters["LightEdit"] as PG.Core.Scene;
            if (item == null)
            {
                return;
            }
            var light = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindLightById( item.Id );
            this.PointLightViewModel.Value = light;
        }
    }
}
