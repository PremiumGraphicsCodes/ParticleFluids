using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Texture
{
    public class TextureEditViewModel : BindableBase, INavigationAware
    {
        private PG.Core.Graphics.Texture PrevTexture;

        public TextureViewModel TextureViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public TextureEditViewModel()
        {
            this.TextureViewModel = new TextureViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            TextureViewModel.Update(PrevTexture);
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Texture"] as PG.Core.Graphics.Texture;
            if (item != null)
            {
                this.PrevTexture = item;
                this.TextureViewModel.Value = item;
            }
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
