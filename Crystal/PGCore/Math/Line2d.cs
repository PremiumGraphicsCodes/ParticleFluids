namespace PG.Core.Math
{
    public class Line2d
    {
        private Vector2d start;
        private Vector2d end;

        public Line2d(Vector2d start, Vector2d end)
        {
            this.start = start;
            this.end = end;
        }

        public Vector2d Start { get { return start; } }

        public Vector2d End { get { return end; } }

        public Vector2d Dir { get { return end - start; } }

        public double Length
        {
            get { return start.Distance(end); }
        }

        public double LengthSquared
        {
            get { return start.DistanceSquared(end); }
        }
    }
}
