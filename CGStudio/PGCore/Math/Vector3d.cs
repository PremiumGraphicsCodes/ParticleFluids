namespace PG.Core.Math
{
    public class Vector3d
    {
        private double x;
        private double y;
        private double z;

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

        public double Z
        {
            get { return z; }
            set { this.z = value; }
        }

        public Vector3d() :
            this(0,0,0)
        {
        }

        public Vector3d(Vector2d v) :
            this(v.X, v.Y, 0.0)
        {
        }

        public Vector3d(Vector2d v, double z) :
            this(v.X, v.Y, z)
        {
        }

        public Vector3d(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static Vector3d Zero()
        {
            return new Vector3d(0, 0, 0);
        }

        public static Vector3d UnitX()
        {
            return new Vector3d(1, 0, 0);
        }

        public static Vector3d UnitY()
        {
            return new Vector3d(0, 1, 0);
        }

        public static Vector3d UnitZ()
        {
            return new Vector3d(0, 0, 1);
        }
        
        public double LengthSquared
        {
            get { return x*x + y*y + z*z; }
        }

        public double Length
        {
            get { return System.Math.Sqrt(LengthSquared); }
        }

        public Vector3d Normalized
        {
            get { return this / Length; }
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

        public double Dot(Vector3d rhs)
        {
            return this.x * rhs.x + this.y * rhs.Y + this.z * rhs.z;
        }

        public Vector3d Cross(Vector3d rhs)
        {
            var xx = this.y * rhs.z - this.z * rhs.y;
            var yy = this.z * rhs.x - this.x * rhs.z;
            var zz = this.x * rhs.y - this.y * rhs.x;
            return new Vector3d(xx, yy, zz);
        }

        public static Vector3d operator+(Vector3d lhs, Vector3d rhs)
        {
            var xx = lhs.x + rhs.x;
            var yy = lhs.y + rhs.y;
            var zz = lhs.z + rhs.z;
            return new Vector3d(xx, yy, zz);
        }

        public static Vector3d operator-(Vector3d lhs, Vector3d rhs)
        {
            var xx = lhs.x - rhs.x;
            var yy = lhs.y - rhs.y;
            var zz = lhs.z - rhs.z;
            return new Vector3d(xx, yy, zz);
        }

        public static Vector3d operator*(Vector3d v, double s)
        {
            return new Vector3d(v.x * s, v.y * s, v.z * s);
        }

        public static Vector3d operator*(double s, Vector3d v)
        {
            return v * s;
        }

        public static Vector3d operator/(Vector3d v, double s)
        {
            return v * (1.0 / s);
        }

        public bool IsSame(Vector3d rhs, double tolerance)
        {
            return DistanceSquared(rhs) < tolerance * tolerance;
        }
    }
}
