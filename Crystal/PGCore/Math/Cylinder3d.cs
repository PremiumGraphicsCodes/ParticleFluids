using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Math
{
    public class Cylinder3d
    {
        private double radius;
        private double height;
        private Vector3d center;

        public Cylinder3d(double radius, double height, Vector3d center)
        {
            this.radius = radius;
            this.height = height;
            this.center = center;
        }
    }
}
