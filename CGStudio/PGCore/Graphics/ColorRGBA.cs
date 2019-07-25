namespace PG.Core.Graphics
{
    public struct ColorRGBA
    {
        private float v1;
        private float v2;
        private float v3;
        private float v4;

        public ColorRGBA(float v1, float v2, float v3, float v4) : this()
        {
            this.v1 = v1;
            this.v2 = v2;
            this.v3 = v3;
            this.v4 = v4;
        }

        public float R { get; set; }
        public float G { get; set; }
        public float B { get; set; }
        public float A { get; set; }

        bool IsSame(ColorRGBA lhs, ColorRGBA rhs, float tolerance)
        {
            return
                System.Math.Abs(lhs.R - rhs.R) < tolerance &&
                System.Math.Abs(lhs.G - rhs.G) < tolerance &&
                System.Math.Abs(lhs.B - rhs.B) < tolerance &&
                System.Math.Abs(lhs.A - rhs.A) < tolerance;
        }
    }
}
