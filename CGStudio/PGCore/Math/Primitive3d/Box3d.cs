using System.Collections.Generic;
using System.Linq;

namespace PG.Core.Math
{
    public class Box3d : IVolume3d
    {
        private Vector3d min;
        private Vector3d max;

        public Vector3d Min
        {
            get { return min; }
        }

        public Vector3d Max
        {
            get { return max; }
        }

        public Box3d()
        {
            this.min = new Vector3d(0, 0, 0);
            this.max = new Vector3d(1, 1, 1);
        }

        public Box3d(Vector3d v)
        {
            this.min = v.Clone();
            this.max = v.Clone();
        }

        public Box3d(Vector3d v1, Vector3d v2) :
            this(v1)
        {
            Add(v2);
        }

        public Box3d(IEnumerable<Vector3d> positions) :
            this(positions.FirstOrDefault())
        {
            foreach (var p in positions)
            {
                Add(p);
            }
        }

        public void Add(Vector3d v)
        {
            min.X = System.Math.Min(min.X, v.X);
            min.Y = System.Math.Min(min.Y, v.Y);
            min.Z = System.Math.Min(min.Z, v.Z);

            max.X = System.Math.Max(max.X, v.X);
            max.Y = System.Math.Max(max.Y, v.Y);
            max.Z = System.Math.Max(max.Z, v.Z);
        }


        public double Volume
        {
            get {
                var v = max - min;
                return v.X * v.Y * v.Z;
            }
        }

        public Vector3d Length
        {
            get { return max - min; }
        }

        public Vector3d Center
        {
            get { return GetPosition(0.5, 0.5, 0.5); }
        }

        public Vector3d GetPosition(double u, double v, double w)
        {
            var l = Length;
            return min + new Vector3d( l.X *u, l.Y * v, l.Z * w);
        }

        public bool IsInside(Vector3d position)
        {
            var xIsIn = (min.X < position.X) && (position.X < max.X);
            var yIsIn = (min.Y < position.Y) && (position.Y < max.Y);
            var zIsIn = (min.Z < position.Z) && (position.Z < max.Z);
            return xIsIn && yIsIn && zIsIn;
        }
    }
}
