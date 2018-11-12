namespace PG.Math
{
    public class Box3d
    {
        private Vector3d min;
        private Vector3d max;

        public Box3d(Vector3d v1, Vector3d v2)
        {
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
    }
}
