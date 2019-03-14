using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control
{
    public class Vector3dViewModel : BindableBase
    {
        public ReactiveProperty<double> X { get; }
            = new ReactiveProperty<double>();

        public ReactiveProperty<double> Y { get; }
            = new ReactiveProperty<double>();

        public ReactiveProperty<double> Z { get; }
            = new ReactiveProperty<double>();

        public Vector3dViewModel()
        {
        }

        public Vector3d Value
        {
            get { return new Vector3d(X.Value, Y.Value, Z.Value); ; }
            set
            {
                X.Value = value.X;
                Y.Value = value.Y;
                Z.Value = value.Z;
            }
        }
    }
}
