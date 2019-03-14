using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrameBuilder
    {
        private readonly List<Edge> edges;

        public WireFrameBuilder()
        {
            this.edges = new List<Edge>();
        }

        public void Build(Box3d box)
        {
            var vertices = new List<Vertex>();
            vertices.Add( new Vertex( box.GetPosition(0.0, 0.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 0.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 1.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(0.0, 1.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(0.0, 0.0, 1.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 0.0, 1.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 1.0, 1.0) ) );
            vertices.Add( new Vertex( box.GetPosition(0.0, 1.0, 1.0) ) );

            edges.Add(new Edge(vertices[0], vertices[1]));
            edges.Add(new Edge(vertices[1], vertices[2]));
            edges.Add(new Edge(vertices[2], vertices[3]));
            edges.Add(new Edge(vertices[3], vertices[0]));

            edges.Add(new Edge(vertices[4], vertices[5]));
            edges.Add(new Edge(vertices[5], vertices[6]));
            edges.Add(new Edge(vertices[6], vertices[7]));
            edges.Add(new Edge(vertices[7], vertices[0]));
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

        public WireFrame WireFrame { get { return new WireFrame(edges); } }
    }
}
