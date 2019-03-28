using Prism.Mvvm;
using Reactive.Bindings;
using System.Windows.Media.Imaging;

namespace PG.Control.Graphics
{
    public class TextureViewModel : BindableBase
    {
        public ReactiveProperty<BitmapImage> Image { get; }

        public TextureViewModel()
        {
            var image = new BitmapImage();
            Image = new ReactiveProperty<BitmapImage>();
            Image.Value = new BitmapImage();
        }
    }
}
