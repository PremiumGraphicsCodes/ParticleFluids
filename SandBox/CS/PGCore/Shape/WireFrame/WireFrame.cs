using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrameEdge
    {
        public int OriginId { get; set; }
        public int DestId { get; set; }

        public WireFrameEdge(int originId, int destId)
        {
            this.OriginId = originId;
            this.DestId = destId;
        }
    }

    public class WireFrame
    {
        public List<Vector3d> Positions { get; set; }
        public List<WireFrameEdge> Edges { get; set; }

        public WireFrame()
        {
            this.Positions = new List<Vector3d>();
        }

        public WireFrame(List<Vector3d> positions, List<WireFrameEdge> edges)
        {
            this.Positions = positions;
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
