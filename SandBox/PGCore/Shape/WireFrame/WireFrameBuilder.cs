using System.Collections.Generic;
using System.Linq;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class WireFrameBuilder
    {
        private readonly List<Vector3d> positions = new List<Vector3d>();
        private readonly List<WireFrameEdge> edges = new List<WireFrameEdge>();

        public WireFrameBuilder()
        {
        }

        public void Add(Line3d line)
        {
            var v1 = CreatePosition(line.GetPosition(0.0));
            var v2 = CreatePosition(line.GetPosition(1.0));
            CreateEdge(v1, v2);
        }

        public void Add(Ellipse3d circle, int udiv)
        {
            var vs = new int[udiv];
            for(int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                vs[i] = CreatePosition(circle.GetPosition(u));
            }
            for(int i = 0; i < udiv-1; ++i)
            {
                CreateEdge(vs[i], vs[i + 1]);
            }
            CreateEdge(vs.LastOrDefault(), vs.FirstOrDefault());
        }

        private void Add(Quad3d quad)
        {
            var v1 = CreatePosition(quad.GetPosition(0.0, 0.0));
            var v2 = CreatePosition(quad.GetPosition(1.0, 0.0));
            var v3 = CreatePosition(quad.GetPosition(1.0, 1.0));
            var v4 = CreatePosition(quad.GetPosition(0.0, 1.0));

            CreateEdge(v1, v2);
            CreateEdge(v2, v3);
            CreateEdge(v3, v4);
            CreateEdge(v4, v1);
        }

        public void Add(Cylinder3d cylinder, int udiv)
        {
            // create top.
            var topCenter = CreatePosition( cylinder.GetPosition(0.0, 0.0, 1.0) );
            var topVertices = new CircularBuffer1d<int>(udiv, 0);
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                topVertices[i] = CreatePosition( cylinder.GetPosition(1.0, u, 1.0) );
            }

            for (int i = 0; i <= udiv; ++i)
            {
                CreateEdge(topCenter, topVertices.Get(i));
            }

            // create bottom.
            var bottomCenter = CreatePosition( cylinder.GetPosition(0.0, 0.0, 0.0) );
            var bottomVertices = new CircularBuffer1d<int>(udiv, 0);
            for (int i = 0; i < udiv; ++i)
            {
                var u = i / (double)udiv;
                bottomVertices[i] = CreatePosition( cylinder.GetPosition(1.0, u, 0.0) );
            }

            for (int i = 0; i <= udiv; ++i)
            {
                CreateEdge(bottomCenter, bottomVertices[i]);
            }

            for (int i = 0; i < udiv; ++i)
            {
                CreateEdge(bottomVertices[i], bottomVertices[i+1]);
                CreateEdge(bottomVertices[i+1], topVertices[i+1]);
                CreateEdge(topVertices[i+1], topVertices[i]);
            }
        }

        public void Add(Cone3d cone, int udiv)
        {
            var topCenter = CreatePosition(cone.GetPosition(0.0, 1.0, 1.0));

            // create bottom.
            var bottomCenter = CreatePosition(cone.GetPosition(0.0, 0.0, 0.0));
            var bottomVertices = new int[udiv + 1];
            for (int i = 0; i <= udiv; ++i)
            {
                var u = i / (double)udiv;
                bottomVertices[i] = CreatePosition(cone.GetPosition(u, 1.0, 0.0));
            }
            for (int i = 0; i <= udiv; ++i)
            {
                CreateEdge(bottomCenter, bottomVertices[i]);
            }

            for (int i = 0; i <= udiv; ++i)
            {
                CreateEdge(topCenter, bottomVertices[i]);
            }

            for (int i = 0; i < udiv; ++i)
            {
                CreateEdge(bottomVertices[i], bottomVertices[i+1]);
            }

        }

        public void Add(Sphere3d surface, int udiv, int vdiv)
        {
            var vertices = new int[udiv+1, vdiv+1];
            for (int i = 0; i <= udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j <= vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i, j] = CreatePosition( surface.GetPosition(u, v) );
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                for (int j = 0; j < vdiv; ++j)
                {
                    CreateEdge(vertices[i, j], vertices[i + 1, j]);
                    CreateEdge(vertices[i, j], vertices[i, j + 1]);
                }
            }
        }

        public void Add(Cylinder3d surface, int udiv, int vdiv)
        {
            var vertices = new int[udiv + 1, vdiv + 1];
            for (int i = 0; i <= udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j <= vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i, j] = CreatePosition(surface.GetPosition(u, v));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                for (int j = 0; j < vdiv; ++j)
                {
                    CreateEdge(vertices[i, j], vertices[i + 1, j]);
                    CreateEdge(vertices[i, j], vertices[i, j + 1]);
                }
            }
        }

        public void Add(Box3d box)
        {
            var vertices = new int[8];
            vertices[0] = CreatePosition(box.GetPosition(0.0, 0.0, 0.0));
            vertices[1] = CreatePosition(box.GetPosition(1.0, 0.0, 0.0));
            vertices[2] = CreatePosition(box.GetPosition(1.0, 1.0, 0.0));
            vertices[3] = CreatePosition(box.GetPosition(0.0, 1.0, 0.0));
            vertices[4] = CreatePosition(box.GetPosition(0.0, 0.0, 1.0));
            vertices[5] = CreatePosition(box.GetPosition(1.0, 0.0, 1.0));
            vertices[6] = CreatePosition(box.GetPosition(1.0, 1.0, 1.0));
            vertices[7] = CreatePosition(box.GetPosition(0.0, 1.0, 1.0));

            CreateEdge(vertices[0], vertices[1]);
            CreateEdge(vertices[1], vertices[2]);
            CreateEdge(vertices[2], vertices[3]);
            CreateEdge(vertices[3], vertices[0]);

            CreateEdge(vertices[4], vertices[5]);
            CreateEdge(vertices[5], vertices[6]);
            CreateEdge(vertices[6], vertices[7]);
            CreateEdge(vertices[7], vertices[4]);

            CreateEdge(vertices[0], vertices[4]);
            CreateEdge(vertices[1], vertices[5]);
            CreateEdge(vertices[2], vertices[6]);
            CreateEdge(vertices[3], vertices[7]);
        }

        public void Add(Torus3d torus, int udiv, int vdiv)
        {
            var vertices = new int[udiv + 1, vdiv + 1];
            for (int i = 0; i <= udiv; ++i)
            {
                var u = i / (double)udiv;
                for (int j = 0; j <= vdiv; ++j)
                {
                    var v = j / (double)vdiv;
                    vertices[i, j] = CreatePosition(torus.GetPosition(u, v));
                }
            }
            for (int i = 0; i < udiv; ++i)
            {
                for (int j = 0; j < vdiv; ++j)
                {
                    CreateEdge(vertices[i, j], vertices[i + 1, j]);
                    CreateEdge(vertices[i, j], vertices[i, j + 1]);
                }
            }
        }

        private void CreateEdge(int originId, int destId)
        {
            edges.Add(new WireFrameEdge(originId, destId));
        }

        private int CreatePosition(Vector3d position)
        {
            positions.Add(position);
            return positions.Count - 1;
        }

        public WireFrame ToWireFrame()
        {
            return new WireFrame(positions, edges);
        }
    }
}
