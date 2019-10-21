using PG.Control.Graphics;
using PG.Core.UI;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class AppearanceViewModel
    {
        public ColorRGBAViewModel ColorViewModel { get; }
            = new ColorRGBAViewModel();

        public ReactiveProperty<float> Size { get; }
            = new ReactiveProperty<float>(1.0f);

        public AppearanceViewModel()
        {
        }

        public ParticleAppearance Value {
            get
            {
                var appearance = new ParticleAppearance
                {
                    Color = ColorViewModel.Value,
                    Size = Size.Value
                };
                return appearance;
            }
        }
    }
}
