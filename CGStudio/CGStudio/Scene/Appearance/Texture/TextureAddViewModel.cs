using PG.Control.Graphics;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Appearance.Texture
{
    public class TextureAddViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Texture01");

        public TextureViewModel TextureViewModel { get; }
            = new TextureViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList world;

        public TextureAddViewModel(SceneList world)
        {
            this.world = world;
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            world.AddTextureScene(TextureViewModel.ImagePath.Value, Name.Value);
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            ;
        }
    }
}
