using PG.Control.Graphics;
using PG.Core.UI;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class AppearanceViewModel
    {
        public ColorRGBAViewModel Color;
        public ReactiveProperty<float> Size;

        public AppearanceViewModel()
        {
            this.Color = new ColorRGBAViewModel();
            this.Size = new ReactiveProperty<float>(1.0f);
        }

        public ParticleAppearance Value {
            get
            {
                var appearance = new ParticleAppearance();
                appearance.Color = Color.Value;
                appearance.Size = Size.Value;
                return appearance;
            }
        }
    }
}
