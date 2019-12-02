namespace PG.Core.Math
{
    public class Vector4d
    {
        private double x;
        private double y;
        private double z;
        private double w;

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

        public double W
        {
            get { return w; }
            set { this.w = value; }
        }

        public Vector4d(Vector3d v, double w)
        {
            this.x = v.X;
            this.y = v.Y;
            this.z = v.Z;
            this.w = w;
        }

        public Vector4d(double x, double y, double z, double w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public double LengthSquared
        {
            get { return x * x + y * y + z * z + w * w; }
        }

        public double Length
        {
            get { return System.Math.Sqrt(LengthSquared); }
        }

        public Vector4d Normalized
        {
            get { return this / Length; }
        }

        public double DistanceSquared(Vector4d rhs)
        {
            var xx = x - rhs.x;
            var yy = y - rhs.y;
            var zz = z - rhs.z;
            var ww = w - rhs.w;
            return (xx * xx + yy * yy + zz * zz + ww * ww);
        }

        public double Distance(Vector4d rhs)
        {
            return System.Math.Sqrt(DistanceSquared(rhs));
        }

        public double Dot(Vector4d rhs)
        {
            return x * rhs.x + y * rhs.Y + z * rhs.z + w * rhs.w;
        }

        public static Vector4d operator +(Vector4d lhs, Vector4d rhs)
        {
            var xx = rhs.x + lhs.x;
            var yy = rhs.y + lhs.y;
            var zz = rhs.z + lhs.z;
            var ww = rhs.w + lhs.w;
            return new Vector4d(xx, yy, zz, ww);
        }

        public static Vector4d operator -(Vector4d lhs, Vector4d rhs)
        {
            var xx = rhs.x - lhs.x;
            var yy = rhs.y - lhs.y;
            var zz = rhs.z - lhs.z;
            var ww = rhs.w - lhs.w;
            return new Vector4d(xx, yy, zz, ww);
        }

        public static Vector4d operator *(Vector4d v, double s)
        {
            return new Vector4d(v.x * s, v.y * s, v.z * s, v.w * s);
        }

        public static Vector4d operator *(double s, Vector4d v)
        {
            return v * s;
        }

        public static Vector4d operator /(Vector4d v, double s)
        {
            return v * (1.0 / s);
        }

        public bool IsSame(Vector4d rhs, double tolerance)
        {
            return DistanceSquared(rhs) < tolerance * tolerance;
        }
    }
}
