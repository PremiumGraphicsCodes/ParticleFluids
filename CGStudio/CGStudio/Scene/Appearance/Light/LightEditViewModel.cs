using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Light
{
    public class LightEditViewModel : BindableBase, INavigationAware
    {
        private PG.Core.Graphics.PointLight PrevLight;

        public PointLightViewModel PointLightViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public LightEditViewModel()
        {
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
        }

        private void OnOk()
        {
            this.PointLightViewModel.Update(this.PrevLight);
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
            var item = navigationContext.Parameters["Light"] as PG.Core.Graphics.PointLight;
            if (item != null)
            {
                this.PrevLight = item;
                this.PointLightViewModel.Value = item;
            }
        }
    }
}
