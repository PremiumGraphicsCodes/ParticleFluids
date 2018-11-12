using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PGWPF.Math
{
    public class Vector3d
    {
        private double x;
        private double y;
        private double z;

        public double X
        {
            get; set;
        }

        public double Y
        {
            get; set;
        }

        public double Z
        {
            get; set;
        }

        public Vector3d(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        
        public double LengthSquared
        {
            get { return x* x + y * y + z * z; }
        }

        public double Length
        {
            get { return System.Math.Sqrt(LengthSquared); }
        }

        public double DistanceSquared(Vector3d rhs)
        {
            var xx = x - rhs.x;
            var yy = y - rhs.y;
            var zz = z - rhs.z;
            return (xx * xx + yy * yy + zz * zz);
        }

        public double Distance(Vector3d rhs)
        {
            return System.Math.Sqrt(DistanceSquared(rhs));
        }
    }
}
