﻿using System;

namespace PG.Core.Math
{
    public class Cone3d : ISurface3d, IVolume3d
    {
        public Cone3d()
        {
            Radius = 1.0;
            Height = 1.0;
            Bottom = new Vector3d(0, 0, 0);
        }

        public Cone3d(double radius, double height, Vector3d bottom)
        {
            Radius = radius;
            Height = height;
            Bottom = bottom;
        }

        public double Radius { get; }

        public double Height { get; }

        public Vector3d Bottom { get; }

        public Vector3d GetPosition(double u, double v)
        {
            return GetPosition(u, v, 1.0);
        }

        public Vector3d GetPosition(double u, double v, double w)
        {
            var circle = ToCircleAt(w);
            return circle.GetPosition(u, v);
        }

        public bool IsInside(Vector3d position)
        {
            throw new NotImplementedException();
        }

        public Circle3d ToCircleAt(double p)
        {
            var radius = Radius * (1.0 - p);
            var z = p * Height;
            var center = Bottom + new Vector3d(0,0,z);
            return new Circle3d(radius, center);
        }
    }
}