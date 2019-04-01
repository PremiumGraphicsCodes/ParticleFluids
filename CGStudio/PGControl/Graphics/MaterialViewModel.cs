using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.Control.Graphics
{
    public class MaterialViewModel
    {
        public ReactiveProperty<int> ID { get; }

        public ColorRGBAViewModel Ambient { get; }

        public ColorRGBAViewModel Diffuse { get; }

        public ColorRGBAViewModel Specular { get; }

        public ReactiveProperty<float> Shininess { get; }

        public MaterialViewModel()
        {
            ID = new ReactiveProperty<int>();
            Ambient = new ColorRGBAViewModel();
            Diffuse = new ColorRGBAViewModel();
            Specular = new ColorRGBAViewModel();
            Shininess = new ReactiveProperty<float>();
        }

        public Core.Graphics.Material Value
        {
            set
            {
                ID.Value = value.ID;
                Ambient.Value = value.Ambient;
                Diffuse.Value = value.Diffuse;
                Specular.Value = value.Specular;
                Shininess.Value = value.Shininess;
            }
        }

        public void Update(Core.Graphics.Material m)
        {
            m.Ambient = Ambient.Value;
            m.Diffuse = Diffuse.Value;
            m.Specular = Specular.Value;
            m.Shininess = Shininess.Value;
        }
    }
}
