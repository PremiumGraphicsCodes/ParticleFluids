namespace PG.Core.Math
{
    public class Torus3d
    {
        public double BigRadius { get; set; }
        public double SmallRadius { get; set; }
        public Vector3d Center { get; set; }

        public Torus3d()
        {
            this.Center = new Vector3d(0, 0, 0);
            this.BigRadius = 1.0;
            this.SmallRadius = 0.5;
        }

        public Torus3d(Vector3d center, double R, double r)
        {
            this.Center = center;
            this.BigRadius = R;
            this.SmallRadius = r;
        }

        public Vector3d GetPosition(double u, double v)
        {
            var t = u * 2.0 * System.Math.PI;
            var p = v * 2.0 * System.Math.PI;
            var x = BigRadius * System.Math.Cos(t) + SmallRadius * System.Math.Cos(p) * System.Math.Cos(t);
            var y = BigRadius * System.Math.Sin(t) + SmallRadius * System.Math.Cos(p) * System.Math.Sin(t);
            var z = SmallRadius * System.Math.Sin(p);
            return Center + new Vector3d(x, y, z);
        }
    }
}