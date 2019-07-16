using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class PolygonMeshBuilder
    {
        private PolygonMesh polygon;

        public PolygonMeshBuilder()
        {
            polygon = new PolygonMesh();
        }

        public PolygonMesh PolygonMesh
        {
            get { return polygon; }
        }

        public void Build(Box3d box, int u, int v)
        {
            /*
            var vertices = new int[u, v];
            for (int i = 0; i < u; ++i)
            {
                var uu = u / (double)i;
                for (int j = 0; j < v; ++j)
                {
                    var vv = j / (double)v;
                    var p = polygon.CreatePosition(box.GetPosition(1.0, u, v));
                    var n = polygon.CreateNormal(box.GetNormal(u, v));
                    var t = polygon.CreateTexCoord(new Vector2d(uu, vv));
                    vertices[i, j] = polygon.CreateVertex(p, n, t);
                }
            }

            for (int i = 0; i < u - 1; ++i)
            {
                for (int j = 0; j < v - 1; ++j)
                {
                    var v1 = vertices[i, j];
                    var v2 = vertices[i + 1, j];
                    var v3 = vertices[i, j + 1];
                    var f = polygon.CreateFace(v1, v2, v3);
                }
            }
            */
        }

        public void Build(Sphere3d sphere, int u, int v)
        {
            var vertices = new int[u, v];
            for (int i = 0; i < u; ++i)
            {
                var uu = i / (double)u;
                for (int j = 0; j < v; ++j)
                {
                    var vv = j / (double)v;
                    var p = polygon.CreatePosition( sphere.GetPosition(1.0, uu, vv) );
                    var n = polygon.CreateNormal( sphere.GetNormal(uu, vv) );
                    var t = polygon.CreateTexCoord( new Vector2d(uu, vv) );
                    vertices[i, j] = polygon.CreateVertex( p, n, t );
                }
            }

            for(int i = 0; i < u-1; ++i)
            {
                for(int j = 0; j < v-1; ++j)
                {
                    var v1 = vertices[i, j];
                    var v2 = vertices[i + 1, j];
                    var v3 = vertices[i, j + 1];
                    var f = polygon.CreateFace(v1, v2, v3);
                }
            }
        }

        public void Build(Cylinder3d cylinder, int u, int v)
        {
            var vertices = new int[u, v];
            for (int i = 0; i < u; ++i)
            {
                var uu = i / (double)u;
                for (int j = 0; j < v; ++j)
                {
                    var vv = j / (double)v;
                    var p = polygon.CreatePosition( cylinder.GetPosition(1.0, uu, vv) );
                    var n = polygon.CreateNormal( cylinder.GetNormal(uu, vv) );
                    vertices[i, j] = polygon.CreateVertex(p, n, -1);
                }
            }

            for (int i = 0; i < u - 1; ++i)
            {
                for (int j = 0; j < v - 1; ++j)
                {
                    var v1 = vertices[i, j];
                    var v2 = vertices[i + 1, j];
                    var v3 = vertices[i, j + 1];
                    var face = polygon.CreateFace(v1, v2, v3);
                }
            }
        }
    }
}
