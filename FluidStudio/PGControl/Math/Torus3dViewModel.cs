using PG.Core.Math;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Torus3dViewModel
    {
        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveProperty<double> BigRadius { get; }
            = new ReactiveProperty<double>(10.0);

        public ReactiveProperty<double> SmallRadius { get; }
            = new ReactiveProperty<double>(1.0);

        public Torus3dViewModel()
        { }

        public Torus3d Value
        {
            get { return new Torus3d(CenterViewModel.Value, BigRadius.Value, SmallRadius.Value); }
            set {
                this.CenterViewModel.Value = value.Center;
                this.SmallRadius.Value = value.SmallRadius;
                this.BigRadius.Value = value.BigRadius;
            }
        }
    }
}
