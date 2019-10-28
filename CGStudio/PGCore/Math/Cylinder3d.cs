namespace PG.Core.Math
{
    public class Cylinder3d : ISurface3d, IVolume3d
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

        public Vector3d GetNormal(double u, double v)
        {
            var p1 = GetPosition(1.0, u, v);
            var p2 = GetPosition(0.0, u, v);
            var vv = p1 - p2;
            return vv.Normalized;
        }

        public Vector3d GetPosition(double u, double v)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = radius * System.Math.Cos(angle);
            var y = radius * System.Math.Sin(angle);
            var z = height * v;
            return new Vector3d(x, y, z);
        }

        public Vector3d GetPosition(double r, double u, double v)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = r * radius * System.Math.Cos(angle);
            var y = r * radius * System.Math.Sin(angle);
            var z = height * v;
            return new Vector3d(x, y, z);
        }

        public bool IsInside(Vector3d position)
        {
            var distance = CalculateDistance(position);
            return distance < 0.0;
        }

        public double CalculateDistance(Vector3d position)
        {
            var bottom = GetPosition(0.0, 0.0, 0.0);
            var top = GetPosition(0.0, 0.0, 1.0);
            var bottomToTop = top - bottom;

            var ptp = position - bottom;            
            var dot = ptp.Dot(bottomToTop);

            var heightSquared = height * height;
            if(dot< 0.0f || dot> heightSquared )
            {
                return( -1.0f );
            }
            else
            {
                var dsq = ptp.LengthSquared - dot* dot / heightSquared;
                if(dsq > heightSquared )
                {
                    return( -1.0f );
                }
                else
                {
                    return System.Math.Sqrt(dsq) - radius;
                }
            }
        }
    }
}
