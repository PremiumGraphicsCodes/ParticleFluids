using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrame
    {
        public List<Line3d> Edges { get; set; }

        public WireFrame()
        {
            this.Edges = new List<Line3d>();
        }

        public WireFrame(List<Line3d> edges)
        {
            this.Edges = edges;
        }

        /*
        public List<Line3d> ToLines()
        {
            foreach(var e in Edges) {
                e.Origin;
            }
        }
        */
    }
}
