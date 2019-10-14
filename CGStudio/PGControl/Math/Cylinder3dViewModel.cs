using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Cylinder3dViewModel : BindableBase
    {
        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveProperty<double> Radius { get; }
            = new ReactiveProperty<double>();

        public ReactiveProperty<double> Height { get; }
            = new ReactiveProperty<double>();

        public Cylinder3d Value
        {
            get
            {
                return new Cylinder3d(Radius.Value, Height.Value, CenterViewModel.Value);
            }
            set
            {
                this.Radius.Value = value.Radius;
                this.Height.Value = value.Height;
                this.CenterViewModel.Value = value.Center;
            }
        }

        public Cylinder3dViewModel()
        {
            this.Radius.Value = 1.0;
            this.Height.Value = 1.0;
        }
    }
}
