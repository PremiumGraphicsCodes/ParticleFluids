namespace PG.Core.Math
{
    public class Sphere3d
    {
        private double radius;
        private Vector3d center;

        public Sphere3d(double radius, Vector3d center)
        {
            this.radius = radius;
            this.center = center;
        }

        public Vector3d GetPosition(double u, double v)
        {
            var theta = u * System.Math.PI * 2.0;
            var phi = v * System.Math.PI;
            return GetPositionByAngle(theta, phi);
        }

        public Vector3d GetPositionByAngle(double theta, double phi)
        {
            var x = radius * System.Math.Sin(theta) * System.Math.Cos(phi);
            var y = radius * System.Math.Sin(theta) * System.Math.Sin(phi);
            var z = radius * System.Math.Cos(theta);
            return new Vector3d(x, y, z);
        }
    }
}
