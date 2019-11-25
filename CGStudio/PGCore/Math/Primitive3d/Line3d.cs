namespace PG.Core.Math
{
    public class Line3d : ICurve3d
    {
        private Vector3d start;
        private Vector3d end;

        public Line3d(Vector3d start, Vector3d end)
        {
            this.start = start;
            this.end = end;
        }

        public Vector3d Start { get { return start; } }

        public Vector3d End { get { return end; } }

        public Vector3d Dir { get { return end - start; } }

        public double Length
        {
            get { return start.Distance(end); }
        }

        public double LengthSquared
        {
            get { return start.DistanceSquared(end); }
        }

        public Vector3d GetPosition(double u)
        {
            var dir = Dir;//.Normalized;
            return start + dir * u;
        }
    }
}
