namespace PG.Core.Math
{
    public class Cylinder3d
    {
        private double radius;
        private double height;
        private Vector3d center;

        public double Radius
        {
            get { return radius; }
            set { this.radius = value; }
        }

        public double Height
        {
            get { return height; }
            set { this.height = value; }
        }

        public Vector3d Center
        {
            get { return center; }
            set { this.center = value; }
        }

        public Cylinder3d() :
            this(1.0, 1.0, new Vector3d())
        {
        }

        public Cylinder3d(double radius, double height, Vector3d center)
        {
            this.radius = radius;
            this.height = height;
            this.center = center;
        }

        public Vector3d GetPosition(double r, double u, double v)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = r * radius * System.Math.Cos(angle);
            var y = r * radius * System.Math.Sin(angle);
            var z = height * v;
            return new Vector3d(x, y, z);
        }

        public Vector3d GetNormal(double u, double v)
        {
            var p1 = GetPosition(1.0, u, v);
            var p2 = GetPosition(0.0, u, v);
            var vv = p1 - p2;
            return vv.Normalized;
        }

    }
}
