namespace PG.Core.Math
{
    public class Circle3d
    {
        private Vector3d center;
        private Vector3d uvec;
        private Vector3d vvec;

        public Vector3d Center
        {
            get { return center; }
            set { this.center = value; }
        }

        public Circle3d() :
            this(new Vector3d(0,0,0), new Vector3d(1,0,0), new Vector3d(0,1,0))
        {
        }

        public Circle3d(Vector3d center, Vector3d uvec, Vector3d vvec)
        {
            this.center = center;
            this.uvec = uvec;
            this.vvec = vvec;
        }

        public Vector3d GetPosition(double u)
        {
            var angle = u * 2.0 * System.Math.PI;
            var x = uvec * System.Math.Cos(angle);
            var y = vvec * System.Math.Sin(angle);
            return center + x + y;
        }

        public Vector3d Normal()
        {
            return uvec.Normalized.Cross(vvec.Normalized);
        }
    }
}


