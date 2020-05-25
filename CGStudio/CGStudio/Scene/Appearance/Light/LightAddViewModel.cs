using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Appearance.Light
{
    public class LightAddViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<string> Name { get; }

        public PointLightViewModel PointLightViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        private readonly World world;

        public LightAddViewModel(World world)
        {
            this.world = world;
            this.Name = new ReactiveProperty<string>("Light");
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            world.Scenes.AddLightScene(PointLightViewModel.Value, Name.Value);
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
        }
    }
}