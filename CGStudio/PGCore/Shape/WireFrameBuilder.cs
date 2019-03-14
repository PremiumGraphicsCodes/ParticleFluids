using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrameBuilder
    {
        private readonly List<Edge> edges;
        private readonly List<Vertex> vertices;

        public WireFrameBuilder()
        {
            this.edges = new List<Edge>();
            this.vertices = new List<Vertex>();
        }

        public void Build(Box3d box)
        {
            vertices.Add( new Vertex( box.GetPosition(0.0, 0.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 0.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 1.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(0.0, 1.0, 0.0) ) );
            vertices.Add( new Vertex( box.GetPosition(0.0, 0.0, 1.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 0.0, 1.0) ) );
            vertices.Add( new Vertex( box.GetPosition(1.0, 1.0, 1.0) ) );
            vertices.Add( new Vertex( box.GetPosition(0.0, 1.0, 1.0) ) );

            CreateEdge(0, 1);
            CreateEdge(1, 2);
            CreateEdge(2, 3);
            CreateEdge(3, 0);

            CreateEdge(4, 5);
            CreateEdge(5, 6);
            CreateEdge(6, 7);
            CreateEdge(7, 4);
        }

        private void CreateEdge(int originIndex, int destIndex)
        {
            var origin = vertices[originIndex];
            var dest = vertices[destIndex];
            edges.Add(new Edge(origin, dest));
        }

        public void Build(Cylinder3d cylinder, int udiv, int vdiv)
        {
            var vertices = new Vertex[udiv,vdiv];
            for(int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for(int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i,j] = new Vertex( cylinder.GetPosition(u, v) );
                }
            }
            for(int i = 0; i < udiv-1; ++i)
            {
                for(int j = 0; j < vdiv-1; ++j)
                {
                    edges.Add(new Edge( vertices[i, j], vertices[i+1,j]) );
                    edges.Add(new Edge( vertices[i, j], vertices[i, j+1]));
                }
            }
        }

        public void Build(Sphere3d sphere, int udiv, int vdiv)
        {
            var vertices = new Vertex[udiv, vdiv];
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j < vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i, j] = new Vertex( sphere.GetPosition(u, v) );
                }
            }
            for (int i = 0; i < udiv - 1; ++i)
            {
                for (int j = 0; j < vdiv - 1; ++j)
                {
                    edges.Add(new Edge(vertices[i, j], vertices[i + 1, j]));
                    edges.Add(new Edge(vertices[i, j], vertices[i, j + 1]));
                }
            }
        }

        public WireFrame WireFrame { get { return new WireFrame(edges); } }
    }
}
