namespace PG.Core.Math
{
    public class Circle2d
    {
        private double radius;
        private Vector2d center;

        public double Radius
        {
            get { return radius; }
            set { this.radius = value; }
        }

        public Vector2d Center
        {
            get { return center; }
            set { this.center = value; }
        }

        public Circle2d() :
            this(1.0, new Vector2d())
        {
        }

        public Circle2d(double radius, Vector2d center)
        {
            this.radius = radius;
            this.center = center;
        }

        public Vector2d GetPosition(double u, double v)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = radius * System.Math.Cos(angle);
            var y = radius * System.Math.Sin(angle);
            return new Vector2d(x, y);
        }
    }
}
