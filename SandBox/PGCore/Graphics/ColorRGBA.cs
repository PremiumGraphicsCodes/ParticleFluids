namespace PG.Core.Graphics
{
    public struct ColorRGBA
    {
        public ColorRGBA(float r, float g, float b, float a) : this()
        {
            this.R = r;
            this.G = g;
            this.B = b;
            this.A = a;
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
