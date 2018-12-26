using PG.Core.Math;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control
{
    public class Sphere3dViewModel : BindableBase
    {
        private Vector3dViewModel centerViewModel;

        public Vector3dViewModel CenterViewModel { get { return centerViewModel; } }

        public Sphere3d Sphere
        {
            get { return new Sphere3d(Radius.Value, centerViewModel.Value); }
        }

        public ReactiveProperty<double> Radius { get; private set; }

        public Sphere3dViewModel()
        {
            this.centerViewModel = new Vector3dViewModel();
            this.Radius = new ReactiveProperty<double>(1.0);
        }
    }
}
