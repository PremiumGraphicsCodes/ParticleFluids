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

        public void Build(Cylinder3d cylinder, int udiv, int vdiv)
        {
            var vertices = new Vector3d[udiv,vdiv];
            for(int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for(int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i,j] = cylinder.GetPosition(u, v);
                }
            }
        }

        public void Build(Sphere3d sphere, int udiv, int vdiv)
        {
            var vertices = new Vector3d[udiv, vdiv];
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i, j] = sphere.GetPosition(u, v);
                }
            }
        }

        public WireFrame WireFrame { get { return new WireFrame(lines); } }
    }
}
