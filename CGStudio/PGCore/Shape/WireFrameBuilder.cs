using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrameBuilder
    {
        private readonly List<Vector3d> vertices;
        private readonly List<Line3d> edges;
        private int nextVertexId;

        public WireFrameBuilder()
        {
            this.vertices = new List<Vector3d>();
            this.edges = new List<Line3d>();
            this.nextVertexId = 0;
        }

        public void Build(Box3d box)
        {
            vertices.Add( box.GetPosition(0.0, 0.0, 0.0) );
            vertices.Add( box.GetPosition(1.0, 0.0, 0.0) );
            vertices.Add( box.GetPosition(1.0, 1.0, 0.0) );
            vertices.Add( box.GetPosition(0.0, 1.0, 0.0) );
            vertices.Add( box.GetPosition(0.0, 0.0, 1.0) );
            vertices.Add( box.GetPosition(1.0, 0.0, 1.0) );
            vertices.Add( box.GetPosition(1.0, 1.0, 1.0) );
            vertices.Add( box.GetPosition(0.0, 1.0, 1.0) );

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
            edges.Add(new Line3d(origin, dest));
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
                    vertices[i,j] = cylinder.GetPosition(1.0, u, v);
                }
            }
            for(int i = 0; i < udiv-1; ++i)
            {
                for(int j = 0; j < vdiv-1; ++j)
                {
                    edges.Add(new Line3d( vertices[i, j], vertices[i+1,j]) );
                    edges.Add(new Line3d( vertices[i, j], vertices[i, j+1]));
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
                    vertices[i, j] = sphere.GetPosition(1.0, u, v);
                }
            }
            for (int i = 0; i < udiv - 1; ++i)
            {
                for (int j = 0; j < vdiv - 1; ++j)
                {
                    edges.Add(new Line3d(vertices[i, j], vertices[i + 1, j]));
                    edges.Add(new Line3d(vertices[i, j], vertices[i, j + 1]));
                }
            }
        }

        public WireFrame WireFrame { get { return new WireFrame(edges); } }
    }
}
