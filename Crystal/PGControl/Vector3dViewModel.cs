using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control
{
    public class Vector3dViewModel : BindableBase
    {
        public ReactiveProperty<double> X { get; private set; }

        public ReactiveProperty<double> Y { get; private set; }

        public ReactiveProperty<double> Z { get; private set; }

        public Vector3dViewModel()
        {
            this.X = new ReactiveProperty<double>(0.0);
            this.Y = new ReactiveProperty<double>(0.0);
            this.Z = new ReactiveProperty<double>(0.0);
        }

        public Vector3d Vector
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
