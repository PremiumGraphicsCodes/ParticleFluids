using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control
{
    public class Cylinder3dViewModel : BindableBase
    {
        private readonly Vector3dViewModel centerViewModel;

        public Vector3dViewModel CenterViewModel { get { return centerViewModel; } }

        public ReactiveProperty<double> Radius { get; private set; }

        public ReactiveProperty<double> Height { get; private set; }

        public Cylinder3dViewModel()
        {
            this.centerViewModel = new Vector3dViewModel();
            this.Radius = new ReactiveProperty<double>(1.0);
            this.Height = new ReactiveProperty<double>(1.0);
        }
    }
}
