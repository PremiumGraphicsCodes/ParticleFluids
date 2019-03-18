using PG.Control.Math;
using PG.Core.Graphics;
using Prism.Mvvm;

namespace PG.Control.Graphics
{
    public class PointLightViewModel : BindableBase
    {
        public PointLightViewModel()
        {
            Position = new Vector3dViewModel();
            Ambient = new ColorRGBAViewModel();
            Diffuse = new ColorRGBAViewModel();
            Specular = new ColorRGBAViewModel();
        }

        public Vector3dViewModel Position { get; }

        public ColorRGBAViewModel Ambient { get; }

        public ColorRGBAViewModel Diffuse { get; }

        public ColorRGBAViewModel Specular { get; }

        public PointLight Value
        {
            get
            {
                var light = new PointLight
                {
                    Position = Position.Value,
                    Ambient = Ambient.Value,
                    Diffuset = Diffuse.Value,
                    Specular = Specular.Value
                };
                return light;
            }
        }
    }
}
