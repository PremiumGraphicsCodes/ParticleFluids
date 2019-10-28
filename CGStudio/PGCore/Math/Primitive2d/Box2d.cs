namespace PG.Core.Math
{
    public class Box2d
    {
        private Vector2d min;
        private Vector2d max;

        public Box2d()
        {
            min = new Vector2d(0, 0);
            max = new Vector2d(1, 1);
        }

        public Vector2d Min
        {
            get { return min; }
            set { this.min = value; }
        }

        public Vector2d Max
        {
            get { return max; }
            set { this.max = value; }
        }

        public Vector2d Lengths
        {
            get { return max - min; }
        }

        public double Area
        {
            get
            {
                var l = Lengths;
                return l.X * l.Y;
            }
        }
    }
}
