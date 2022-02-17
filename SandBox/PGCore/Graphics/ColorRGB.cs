namespace PG.Core.Graphics
{
    public struct ColorRGB
    {
        public float R { get; set; }
        public float G { get; set; }
        public float B { get; set; }

        bool IsSame(ColorRGB lhs, ColorRGB rhs, float tolerance)
        {
            return
                System.Math.Abs(lhs.R - rhs.R) < tolerance &&
                System.Math.Abs(lhs.G - rhs.G) < tolerance &&
                System.Math.Abs(lhs.B - rhs.B) < tolerance;
        }
    }
}
