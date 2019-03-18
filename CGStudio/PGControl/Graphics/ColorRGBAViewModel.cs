using PG.Core.Graphics;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Graphics
{
    public class ColorRGBAViewModel : BindableBase
    {
        public ReactiveProperty<byte> R { get; }
            = new ReactiveProperty<byte>();

        public ReactiveProperty<byte> G { get; }
            = new ReactiveProperty<byte>();

        public ReactiveProperty<byte> B { get; }
                = new ReactiveProperty<byte>();

        public ReactiveProperty<byte> A { get; }
            = new ReactiveProperty<byte>();

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
        }
    }
}
