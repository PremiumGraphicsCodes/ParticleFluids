using PG.Core.Math;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Matrix4dViewModel
    {
        public ReactiveProperty<double> X00 { get; }

        public ReactiveProperty<double> X01 { get; }

        public ReactiveProperty<double> X02 { get; }

        public ReactiveProperty<double> X03 { get; }

        public ReactiveProperty<double> X10 { get; }

        public ReactiveProperty<double> X11 { get; }

        public ReactiveProperty<double> X12 { get; }

        public ReactiveProperty<double> X13 { get; }

        public ReactiveProperty<double> X20 { get; }

        public ReactiveProperty<double> X21 { get; }

        public ReactiveProperty<double> X22 { get; }

        public ReactiveProperty<double> X23 { get; }

        public ReactiveProperty<double> X30 { get; }

        public ReactiveProperty<double> X31 { get; }

        public ReactiveProperty<double> X32 { get; }

        public ReactiveProperty<double> X33 { get; }

        public Matrix4dViewModel()
        {
            X00 = new ReactiveProperty<double>(1);
            X01 = new ReactiveProperty<double>(0);
            X02 = new ReactiveProperty<double>(0);
            X03 = new ReactiveProperty<double>(0);

            X10 = new ReactiveProperty<double>(0);
            X11 = new ReactiveProperty<double>(1);
            X12 = new ReactiveProperty<double>(0);
            X13 = new ReactiveProperty<double>(0);

            X20 = new ReactiveProperty<double>(0);
            X21 = new ReactiveProperty<double>(0);
            X22 = new ReactiveProperty<double>(1);
            X23 = new ReactiveProperty<double>(0);

            X30 = new ReactiveProperty<double>(0);
            X31 = new ReactiveProperty<double>(0);
            X32 = new ReactiveProperty<double>(0);
            X33 = new ReactiveProperty<double>(1);
        }

        public Matrix4d Value
        {
            get
            {
                return new Matrix4d
                    (
                    X00.Value, X01.Value, X02.Value, X03.Value,
                    X10.Value, X11.Value, X12.Value, X13.Value,
                    X20.Value, X21.Value, X22.Value, X23.Value,
                    X30.Value, X31.Value, X32.Value, X33.Value
                    );
            }
            set
            {
                X00.Value = value.X00;
                X01.Value = value.X01;
                X02.Value = value.X02;
                X03.Value = value.X03;
                X10.Value = value.X10;
                X11.Value = value.X11;
                X12.Value = value.X12;
                X13.Value = value.X13;
                X20.Value = value.X20;
                X21.Value = value.X12;
                X22.Value = value.X22;
                X23.Value = value.X23;
                X30.Value = value.X30;
                X31.Value = value.X31;
                X32.Value = value.X32;
                X33.Value = value.X33;
            }
        }
    }
}
