using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Appearance.Material
{
    public class MaterialAddViewModel : BindableBase, INavigationAware
    {
        public MaterialViewModel MaterialViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        private readonly World world;

        public MaterialAddViewModel(World world)
        {
            this.world = world;
            this.MaterialViewModel = new MaterialViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            world.Scenes.AddMaterialScene(MaterialViewModel.Value, "Material");
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }
    }
}