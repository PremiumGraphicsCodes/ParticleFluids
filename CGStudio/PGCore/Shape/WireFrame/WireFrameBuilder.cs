using System.Collections.Generic;
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

        public void Build(Cylinder3d cylinder, int udiv)
        {
            // create side.
            var topCenter = CreatePosition( cylinder.GetPosition(0.0, 0.0, 1.0) );
            var topVertices = new int[udiv + 1];
            for (int i = 0; i <= udiv; ++i)
            {
                var u = i / (double)udiv;
                topVertices[i] = CreatePosition( cylinder.GetPosition(1.0, u, 1.0) );
            }

            for (int i = 0; i < udiv; ++i)
            {
                CreateEdge(topCenter, topVertices[i]);
            }

            // create bottom.
            var bottomCenter = CreatePosition( cylinder.GetPosition(0.0, 0.0, 0.0) );
            var bottomVertices = new int[udiv + 1];
            for (int i = 0; i <= udiv; ++i)
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
                CreateEdge(bottomVertices[i+1], topVertices[i + 1]);
                CreateEdge(topVertices[i + 1], topVertices[i]);
            }
        }

        public void Build(ISurface3d surface, int udiv, int vdiv)
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

        public void Build(Box3d box)
        {
            CreatePosition(box.GetPosition(0.0, 0.0, 0.0));
            CreatePosition(box.GetPosition(1.0, 0.0, 0.0));
            CreatePosition(box.GetPosition(1.0, 1.0, 0.0));
            CreatePosition(box.GetPosition(0.0, 1.0, 0.0));
            CreatePosition(box.GetPosition(0.0, 0.0, 1.0));
            CreatePosition(box.GetPosition(1.0, 0.0, 1.0));
            CreatePosition(box.GetPosition(1.0, 1.0, 1.0));
            CreatePosition(box.GetPosition(0.0, 1.0, 1.0));

            CreateEdge(0, 1);
            CreateEdge(1, 2);
            CreateEdge(2, 3);
            CreateEdge(3, 0);

            CreateEdge(4, 5);
            CreateEdge(5, 6);
            CreateEdge(6, 7);
            CreateEdge(7, 4);

            CreateEdge(0, 4);
            CreateEdge(1, 5);
            CreateEdge(2, 6);
            CreateEdge(3, 7);
        }

        private void CreateEdge(int originId, int destId)
        {
            edges.Add(new WireFrameEdge(originId, destId));
        }

        public int CreatePosition(Vector3d position)
        {
            positions.Add(position);
            return positions.Count - 1;
        }


        public WireFrame WireFrame { get { return new WireFrame(positions, edges); } }
    }
}
