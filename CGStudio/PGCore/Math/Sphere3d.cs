﻿namespace PG.Core.Math
{
    public class Sphere3d
    {
        private double radius;
        private Vector3d center;

        public double Radius
        {
            get { return radius; }
            set { this.radius = value; }
        }

        public Vector3d Center
        {
            get { return center; }
            set { this.center = value; }
        }

        public Sphere3d(double radius, Vector3d center)
        {
            this.radius = radius;
            this.center = center;
        }

        public Vector3d GetPosition(double u, double v)
        {
            var theta = u * System.Math.PI * 2.0;
            var phi = v * System.Math.PI;

            var x = radius * System.Math.Sin(theta) * System.Math.Cos(phi);
            var y = radius * System.Math.Sin(theta) * System.Math.Sin(phi);
            var z = radius * System.Math.Cos(theta);
            return new Vector3d(x, y, z);
        }

        public Vector3d GetNormal(double u, double v)
        {
            var vv = GetPosition(u, v) - Center;
            return vv.Normalized;
        }

    }
}
