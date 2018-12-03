using PG.Core.Math;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Control
{
    public class Vector3dViewModel : BindableBase
    {
        private double x;
        private double y;
        private double z;

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
