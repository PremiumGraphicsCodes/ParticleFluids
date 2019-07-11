using Reactive.Bindings;

namespace PG.Control.Graphics
{
    public class MaterialViewModel
    {
        public ColorRGBAViewModel Ambient { get; }

        public ColorRGBAViewModel Diffuse { get; }

        public ColorRGBAViewModel Specular { get; }

        public ReactiveProperty<float> Shininess { get; }

        public MaterialViewModel()
        {
            Ambient = new ColorRGBAViewModel();
            Diffuse = new ColorRGBAViewModel();
            Specular = new ColorRGBAViewModel();
            Shininess = new ReactiveProperty<float>();
        }

        public Core.Graphics.Material Value
        {
            get
            {
                var m = new Core.Graphics.Material
                {
                    Ambient = Ambient.Value,
                    Diffuse = Diffuse.Value,
                    Specular = Specular.Value,
                    Shininess = Shininess.Value
                };
                return m;
            }
            set
            {
                Ambient.Value = value.Ambient;
                Diffuse.Value = value.Diffuse;
                Specular.Value = value.Specular;
                Shininess.Value = value.Shininess;
            }
        }
    }
}
