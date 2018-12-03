using PG.Core.Math;
using Prism.Mvvm;

namespace PG.Control
{
    public class Sphere3dViewModel : BindableBase
    {
        private double x;
        private double y;
        private double z;

        public Sphere3dViewModel()
        {            
        }

        public double X
        {
            get { return x; }
            set { this.SetProperty(ref x, value); }
        }

        public double Y
        {
            get { return y; }
            set { this.SetProperty(ref y, value); }
        }

        public double Z
        {
            get { return z; }
            set { this.SetProperty(ref z, value); }
        }

        public Vector3d Vector
        {
            get { return new Vector3d(x, y, z); ; }
            set
            {
                X = value.X;
                Y = value.Y;
                Z = value.Z;
            }
        }
    }
}
