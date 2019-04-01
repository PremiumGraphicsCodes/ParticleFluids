using PG.Core.Graphics;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Graphics
{
    public class ColorRGBAViewModel : BindableBase
    {
        public ReactiveProperty<float> R { get; }
            = new ReactiveProperty<float>();

        public ReactiveProperty<float> G { get; }
            = new ReactiveProperty<float>();

        public ReactiveProperty<float> B { get; }
                = new ReactiveProperty<float>();

        public ReactiveProperty<float> A { get; }
            = new ReactiveProperty<float>();

        public ColorRGBA Value
        {
            get {
                var c = new ColorRGBA
                {
                    R = R.Value,
                    G = G.Value,
                    B = B.Value,
                    A = A.Value
                };
                return c;
            }

            set
            {
                R.Value = value.R;
                G.Value = value.G;
                B.Value = value.B;
                A.Value = value.A;
            }
        }
    }
}
