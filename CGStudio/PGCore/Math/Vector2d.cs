namespace PG.Core.Math
{
    public class Vector2d
    {
        private double x;
        private double y;

        public double X
        {
            get { return x; }
            set { this.x = value; }
        }

        public double Y
        {
            get { return y; }
            set { this.y = value; }
        }

        public Vector2d()
        {
            this.x = 0.0;
            this.y = 0.0;
        }

        public Vector2d(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        public Vector2d Zero()
        {
            return new Vector2d(0.0, 0.0);
        }

        public Vector2d UnitX()
        {
            return new Vector2d(1.0, 0.0);
        }

        public Vector2d UnitY()
        {
            return new Vector2d(0.0, 1.0);
        }

        public double LengthSquared
        {
            get { return x * x + y * y; }
        }

        public double Length
        {
            get { return System.Math.Sqrt(LengthSquared); }
        }

        public Vector2d Normalized
        {
            get { return this / Length; }
        }

        public double DistanceSquared(Vector2d rhs)
        {
            var xx = x - rhs.x;
            var yy = y - rhs.y;
            return (xx * xx + yy * yy);
        }

        public double Distance(Vector2d rhs)
        {
            return System.Math.Sqrt(DistanceSquared(rhs));
        }

        public double Dot(Vector2d rhs)
        {
            return this.x * rhs.x + this.y * rhs.y;
        }

        public static Vector2d operator +(Vector2d lhs, Vector2d rhs)
        {
            var xx = rhs.x + lhs.x;
            var yy = rhs.y + lhs.y;
            return new Vector2d(xx, yy);
        }

        public static Vector2d operator -(Vector2d lhs, Vector2d rhs)
        {
            var xx = rhs.x - lhs.x;
            var yy = rhs.y - lhs.y;
            return new Vector2d(xx, yy);
        }

        public static Vector2d operator *(Vector2d v, double s)
        {
            return new Vector2d(v.x * s, v.y * s);
        }

        public static Vector2d operator *(double s, Vector2d v)
        {
            return v * s;
        }

        public static Vector2d operator /(Vector2d v, double s)
        {
            return v * (1.0 / s);
        }

        public bool IsSame(Vector2d rhs, double tolerance)
        {
            return DistanceSquared(rhs) < tolerance * tolerance;
        }
    }
}
