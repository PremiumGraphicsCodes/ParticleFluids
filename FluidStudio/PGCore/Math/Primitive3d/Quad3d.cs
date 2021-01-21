namespace PG.Core.Math
{
    public class Quad3d
    {
        public Vector3d Origin { get; }

        public Vector3d UVec { get; }

        public Vector3d VVec { get; }

        public Quad3d()
        {
            this.Origin = new Vector3d(0, 0, 0);
            this.UVec = new Vector3d(1, 0, 0);
            this.VVec = new Vector3d(0, 1, 0);
        }

        public Quad3d(Vector3d origin, Vector3d uvec, Vector3d vvec)
        {
            this.Origin = origin;
            this.UVec = uvec;
            this.VVec = vvec;
        }

        public Vector3d GetPosition(double u, double v)
        {
            return Origin + UVec * u + VVec * v;
        }
    }
}
