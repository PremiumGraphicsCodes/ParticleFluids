using PG.Core.Math;

namespace PG.Core.Shape
{
    public class Edge
    {
        public Edge(Vertex origin, Vertex dest)
        {
            this.Origin = origin;
            this.Dest = dest;
        }

        public Vertex Origin { get; set; }

        public Vertex Dest { get; set; }

        public Line3d ToLine()
        {
            return new Line3d(Origin.Position, Dest.Position);
        }
    }
}
