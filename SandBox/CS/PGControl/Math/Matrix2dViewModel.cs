using PG.Core.Math;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Matrix2dViewModel
    {
        public ReactiveProperty<double> X00 { get; }

        public ReactiveProperty<double> X01 { get; }

        public ReactiveProperty<double> X10 { get; }

        public ReactiveProperty<double> X11 { get; }

        public Matrix2dViewModel()
        {
            X00 = new ReactiveProperty<double>();
            X01 = new ReactiveProperty<double>();

            X10 = new ReactiveProperty<double>();
            X11 = new ReactiveProperty<double>();
        }

        public Matrix2d Value
        {
            get
            {
                return new Matrix2d
                    (
                    X00.Value, X01.Value,
                    X10.Value, X11.Value
                    );
            }
            set
            {
                X00.Value = value.X00;
                X01.Value = value.X01;
                X10.Value = value.X10;
                X11.Value = value.X11;
            }
        }
    }
}
