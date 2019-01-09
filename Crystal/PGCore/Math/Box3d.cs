namespace PG.Core.Math
{
    public class Box3d
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

        public Box3d(Vector3d v1, Vector3d v2)
        {
            this.min = new Vector3d(0,0,0);
            this.max = new Vector3d(0,0,0);

            min.X = System.Math.Min(v1.X, v2.X);
            min.Y = System.Math.Min(v1.Y, v2.Y);
            min.Z = System.Math.Min(v1.Z, v2.Z);

            max.X = System.Math.Max(v1.X, v2.X);
            max.Y = System.Math.Max(v1.Y, v2.Y);
            max.Z = System.Math.Max(v1.Z, v2.Z);
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

        public Vector3d GetPosition(double u, double v, double w)
        {
            var l = Length;
            return min + new Vector3d( l.X *u, l.Y * v, l.Z * w);
        }
    }
}
