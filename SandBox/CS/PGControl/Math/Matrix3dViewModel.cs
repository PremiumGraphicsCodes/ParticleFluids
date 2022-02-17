using PG.Core.Math;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Matrix3dViewModel
    {
        public ReactiveProperty<double> X00 { get; }

        public ReactiveProperty<double> X01 { get; }

        public ReactiveProperty<double> X02 { get; }

        public ReactiveProperty<double> X10 { get; }

        public ReactiveProperty<double> X11 { get; }

        public ReactiveProperty<double> X12 { get; }        

        public ReactiveProperty<double> X20 { get; }

        public ReactiveProperty<double> X21 { get; }

        public ReactiveProperty<double> X22 { get; }

        public Matrix3dViewModel()
        {
            X00 = new ReactiveProperty<double>();
            X01 = new ReactiveProperty<double>();
            X02 = new ReactiveProperty<double>();

            X10 = new ReactiveProperty<double>();
            X11 = new ReactiveProperty<double>();
            X12 = new ReactiveProperty<double>();

            X20 = new ReactiveProperty<double>();
            X21 = new ReactiveProperty<double>();
            X22 = new ReactiveProperty<double>();
        }

        public Matrix3d Value
        {
            get
            {
                return new Matrix3d
                    (
                    X00.Value, X01.Value, X02.Value,
                    X10.Value, X11.Value, X12.Value,
                    X20.Value, X21.Value, X22.Value
                    );
            }
            set
            {
                X00.Value = value.X00;
                X01.Value = value.X01;
                X02.Value = value.X02;
                X10.Value = value.X10;
                X11.Value = value.X11;
                X12.Value = value.X12;
                X20.Value = value.X20;
                X21.Value = value.X12;
                X22.Value = value.X22;
            }
        }
    }
}
