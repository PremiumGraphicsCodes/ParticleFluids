using PG.Control.Graphics;
using PG.Core.UI;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class AppearanceViewModel
    {
        public ColorRGBAViewModel Color;
        public ReactiveProperty<float> Width { get; }

        public AppearanceViewModel()
        {
            Color = new ColorRGBAViewModel();
            Width = new ReactiveProperty<float>(1.0f);
        }

        public WireAppearance Value
        {
            get
            {
                var appearance = new WireAppearance
                {
                    Color = Color.Value,
                    Width = Width.Value
                };
                return appearance;
            }
        }

    }
}
