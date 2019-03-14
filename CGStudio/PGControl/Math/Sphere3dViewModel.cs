using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Math
{
    public class Sphere3dViewModel : BindableBase
    {
        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveProperty<double> Radius { get; }
            = new ReactiveProperty<double>(1.0);

        public Sphere3d Value
        {
            get { return new Sphere3d(Radius.Value, CenterViewModel.Value); }
        }

        public Sphere3dViewModel()
        {
            this.Radius.Value = 1.0;
        }
    }
}
