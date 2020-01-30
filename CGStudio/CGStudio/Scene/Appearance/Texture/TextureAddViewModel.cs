using PG.Control.Graphics;
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

        public TextureAddViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            World.Instance.Scenes.AddTextureScene(TextureViewModel.ImagePath.Value, Name.Value);
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
