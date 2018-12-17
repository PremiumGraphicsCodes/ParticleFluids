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
            var vertices = new List<Vector3d>();
            vertices.Add( box.GetPosition(0.0, 0.0, 0.0) );
            vertices.Add( box.GetPosition(1.0, 0.0, 0.0) );
            vertices.Add( box.GetPosition(1.0, 1.0, 0.0) );
            vertices.Add( box.GetPosition(0.0, 1.0, 0.0) );
            vertices.Add( box.GetPosition(0.0, 0.0, 1.0) );
            vertices.Add( box.GetPosition(1.0, 0.0, 1.0) );
            vertices.Add( box.GetPosition(1.0, 1.0, 1.0) );
            vertices.Add( box.GetPosition(0.0, 1.0, 1.0) );

            lines.Add(new Line3d(vertices[0], vertices[1]));
            lines.Add(new Line3d(vertices[1], vertices[2]));
            lines.Add(new Line3d(vertices[2], vertices[3]));
            lines.Add(new Line3d(vertices[4], vertices[0]));

            lines.Add(new Line3d(vertices[5], vertices[6]));
            lines.Add(new Line3d(vertices[6], vertices[7]));
            lines.Add(new Line3d(vertices[7], vertices[8]));
            lines.Add(new Line3d(vertices[8], vertices[0]));
        }

        public WireFrame WireFrame { get { return new WireFrame(lines); } }
    }
}
