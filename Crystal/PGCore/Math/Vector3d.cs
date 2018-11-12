﻿namespace PG.Math
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
            var xx = rhs.x + lhs.x;
            var yy = rhs.y + lhs.y;
            var zz = rhs.z + lhs.z;
            return new Vector3d(xx, yy, zz);
        }

        public static Vector3d operator-(Vector3d lhs, Vector3d rhs)
        {
            var xx = rhs.x - lhs.x;
            var yy = rhs.y - lhs.y;
            var zz = rhs.z - lhs.z;
            return new Vector3d(xx, yy, zz);
        }
    }
}
