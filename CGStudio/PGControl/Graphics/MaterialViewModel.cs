using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Graphics
{
    public class MaterialViewModel : BindableBase
    {
        public ColorRGBAViewModel Ambient { get; }

        public ColorRGBAViewModel Diffuse { get; }

        public ColorRGBAViewModel Specular { get; }

        public ReactiveProperty<int> Shininess { get; }

        public MaterialViewModel()
        {
            Ambient = new ColorRGBAViewModel();
            Diffuse = new ColorRGBAViewModel();
            Specular = new ColorRGBAViewModel();
            Shininess = new ReactiveProperty<int>();
        }
    }
}
