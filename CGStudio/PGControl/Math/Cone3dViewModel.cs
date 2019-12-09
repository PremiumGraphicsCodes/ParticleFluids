using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Cone3dViewModel : BindableBase
    {
        public Vector3dViewModel BottomViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveProperty<double> Radius { get; }
            = new ReactiveProperty<double>(1.0);

        public ReactiveProperty<double> Height { get; }
            = new ReactiveProperty<double>(1.0);

        public Cone3dViewModel()
        {
        }

        public Cone3d Value
        {
            get
            {
                return new Cone3d(Radius.Value, Height.Value, BottomViewModel.Value);
            }
            set
            {
                this.BottomViewModel.Value = value.Bottom;
                this.Radius.Value = value.Radius;
                this.Height.Value = value.Height;
            }
        }
    }
}
