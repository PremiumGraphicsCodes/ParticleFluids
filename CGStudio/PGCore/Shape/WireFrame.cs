using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrame
    {
        public List<Edge> Edges { get; set; }

        public WireFrame()
        {
            this.Edges = new List<Edge>();
        }

        public WireFrame(List<Edge> edges)
        {
            this.Edges = edges;
        }
    }
}
