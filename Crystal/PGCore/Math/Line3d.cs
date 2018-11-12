namespace PG.Math
{
    public class Line3d
    {
        private Vector3d start;
        private Vector3d end;

        public Line3d(Vector3d start, Vector3d end)
        {
            this.start = start;
            this.end = end;
        }

        public double Length
        {
            get { return start.Distance(end); }
        }
    }
}
