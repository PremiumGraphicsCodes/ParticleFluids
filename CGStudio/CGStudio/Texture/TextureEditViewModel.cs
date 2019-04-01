using PG.Control.Graphics;
using Reactive.Bindings;

namespace PG.CGStudio.Texture
{
    public class TextureEditViewModel
    {
        public TextureViewModel TextureViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public TextureEditViewModel()
        {
            this.TextureViewModel = new TextureViewModel();
            this.OKCommand = new ReactiveCommand();
        }
    }
}
