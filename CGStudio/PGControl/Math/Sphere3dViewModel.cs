using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Sphere3dViewModel : BindableBase
    {
        public Vector3dViewModel CenterViewModel { get; }

        public ReactiveProperty<double> Radius { get; }

        public Sphere3dViewModel()
        {
            this.CenterViewModel = new Vector3dViewModel();
            this.Radius = new ReactiveProperty<double>(1.0);
            this.Radius.Value = 1.0;
        }

        public Sphere3d Value
        {
            get
            {
                return new Sphere3d(Radius.Value, CenterViewModel.Value);
            }

            set
            {
                this.CenterViewModel.Value = value.Center;
                this.Radius.Value = value.Radius;
            }
        }
    }
}
