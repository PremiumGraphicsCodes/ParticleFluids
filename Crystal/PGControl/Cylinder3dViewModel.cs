using Prism.Mvvm;

namespace PG.Control
{
    public class Cylinder3dViewModel : BindableBase
    {
        private double radius;
        private double height;
        private readonly Vector3dViewModel centerViewModel;

        public Vector3dViewModel CenterViewModel { get { return centerViewModel; } }

        public double Radius
        {
            get { return radius; }
            set { SetProperty(ref radius, value); }
        }

        public double Height
        {
            get { return height; }
            set { SetProperty(ref height, value); }
        }

        public Cylinder3dViewModel()
        {
            this.centerViewModel = new Vector3dViewModel();
            this.radius = 1.0;
            this.height = 1.0;
        }
    }
}
