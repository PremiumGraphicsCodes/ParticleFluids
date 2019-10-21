using PG.Control.Graphics;
using PG.Core.UI;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.WireFrame
{
    public class AppearanceViewModel
    {
        public ColorRGBAViewModel ColorViewModel { get; }
            = new ColorRGBAViewModel();

        public ReactiveProperty<float> Width { get; }
            = new ReactiveProperty<float>(1.0f);      

        public AppearanceViewModel()
        {
        }

        public WireAppearance Value
        {
            get
            {
                var appearance = new WireAppearance
                {
                    Color = ColorViewModel.Value,
                    Width = Width.Value
                };
                return appearance;
            }
            set
            {
                ColorViewModel.Value = value.Color;
                Width.Value = value.Width;
            }
        }

    }
}
