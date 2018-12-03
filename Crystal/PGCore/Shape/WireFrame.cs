using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrame
    {
        private List<Line3d> lines;

        public List<Line3d> Lines
        {
            get { return lines; }
            set { this.lines = value; }
        }

        public WireFrame()
        {
            this.lines = new List<Line3d>();
        }
    }
}
