using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Core.Math
{
    public class Circle3d : ICurve3d, ISurface3d
    {
        public double Radius { get; }

        public Vector3d Center { get; }
            = new Vector3d(0, 0, 0);

        public Circle3d() :
            this(1.0, new Vector3d(0,0,0))
        { }

        public Circle3d(double radius, Vector3d center)
        {
            this.Radius = radius;
            this.Center = center;
        }

        public Vector3d GetPosition(double u)
        {
            return GetPosition(u, 1.0);
        }

        public Vector3d GetPosition(double u, double v)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = v * Radius * System.Math.Cos(angle);
            var y = v * Radius * System.Math.Sin(angle);
            return Center + new Vector3d(x, y, 0.0);
        }

        public bool IsSame(Circle3d rhs, double tolerance)
        {
            return this.Center.IsSame(rhs.Center, tolerance) &&
                System.Math.Abs(this.Radius - rhs.Radius) < tolerance;
        }

    }
}
