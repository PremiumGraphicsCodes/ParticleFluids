namespace PG.Core.Math
{
    public class Triangle3d
    {
        public Vector3d v1 { get; set; }
        public Vector3d v2 { get; set; }
        public Vector3d v3 { get; set; }

        public Triangle3d(Vector3d v1, Vector3d v2, Vector3d v3)
        {
            this.v1 = v1;
            this.v2 = v2;
            this.v3 = v3;
        }

        public Vector3d Normal
        {
            get
            {
                var v21 = (v2 - v1).Normalized;
                var v31 = (v3 - v1).Normalized;
                return v21.Cross(v31);
            }
        }
    }
}
