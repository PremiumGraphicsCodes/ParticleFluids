using PG.Core.Math;
using Prism.Mvvm;

namespace PG.Control
{
    public class Sphere3dViewModel : BindableBase
    {
        private Vector3dViewModel centerViewModel;
        private double radius;

        public Vector3dViewModel CenterViewModel { get { return centerViewModel; } }

        public Sphere3d Sphere
        {
            get { return new Sphere3d(radius, centerViewModel.Vector); }
        }

        public double Radius
        {
            get { return radius; }
            set { SetProperty(ref radius, value); }
        }

        public Sphere3dViewModel()
        {
            this.centerViewModel = new Vector3dViewModel();
            this.radius = 1.0;
        }
    }
}
