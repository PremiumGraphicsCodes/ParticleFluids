using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrameBuilder
    {
        private readonly List<Line3d> lines;

        public WireFrameBuilder()
        {
            this.lines = new List<Line3d>();
        }

        public void Build(Box3d box)
        {

        }

        public WireFrame WireFrame { get { return new WireFrame(lines); } }
    }
}
