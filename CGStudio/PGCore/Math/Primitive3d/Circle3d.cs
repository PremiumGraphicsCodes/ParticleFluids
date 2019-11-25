using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Core.Math.Primitive3d
{
    public class Circle3d
    {
        private Vector3d center;
        private Vector3d uvec;
        private Vector3d vvec;

        public Vector3d Center
        {
            get { return center; }
            set { this.center = value; }
        }

        /*
        public Circle3d() :
            this(1.0, new Vector3d())
        {
        }

        public Circle2d(double radius, Vector2d center)
        {
            this.radius = radius;
            this.center = center;
        }


        public Vector3d GetPosition(double u)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = uvec * System.Math.Cos(angle);
            var y = vvec * System.Math.Sin(angle);
            return x + y;
        }
        */
    }
}


