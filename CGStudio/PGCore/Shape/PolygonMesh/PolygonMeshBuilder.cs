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

        public void Build(Box3d box)
        {
            var p0 = polygon.CreatePosition(box.GetPosition(0, 0, 0));
            var p1 = polygon.CreatePosition(box.GetPosition(1, 0, 0));
            var p2 = polygon.CreatePosition(box.GetPosition(1, 1, 0));
            var p3 = polygon.CreatePosition(box.GetPosition(0, 1, 0));

            var p4 = polygon.CreatePosition(box.GetPosition(0, 0, 1));
            var p5 = polygon.CreatePosition(box.GetPosition(1, 0, 1));
            var p6 = polygon.CreatePosition(box.GetPosition(1, 1, 1));
            var p7 = polygon.CreatePosition(box.GetPosition(0, 1, 1));

	        Add(p0, p1, p2, p3); // front
	        Add(p7, p6, p5, p4); // back
	        Add(p3, p2, p6, p7); // top
	        Add(p0, p1, p5, p4); // bottom
	        Add(p0, p4, p7, p3); // left
	        Add(p1, p5, p6, p2); // right
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
                    var p = polygon.CreatePosition(sphere.GetPosition(1.0, uu, vv));
                    var n = polygon.CreateNormal(sphere.GetNormal(uu, vv));
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
                    var v4 = vertices[i + 1, j + 1];
                    polygon.CreateFace(v1, v2, v3);
                    polygon.CreateFace(v4, v3, v2);
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
                    var p = polygon.CreatePosition(cylinder.GetPosition(1.0, uu, vv));
                    var n = polygon.CreateNormal(cylinder.GetNormal(uu, vv));
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
                    var v4 = vertices[i + 1, j + 1];
                    polygon.CreateFace(v1, v2, v3);
                    polygon.CreateFace(v4, v3, v2);
                }
            }
        }

        private void Add(int v0, int v1, int v2, int v3)
        {
            var positions = polygon.Positions;
            var p0 = positions[v0];
            var p1 = positions[v1];
            var p2 = positions[v2];

            var normal = (p1 - p0).Cross(p2 - p0);
            var n0 = polygon.CreateNormal(normal);

            var vv0 = polygon.CreateVertex(v0, n0);
            var vv1 = polygon.CreateVertex(v1, n0);
            var vv2 = polygon.CreateVertex(v2, n0);
            var vv3 = polygon.CreateVertex(v3, n0);

            polygon.CreateFace(vv0, vv1, vv2);
            polygon.CreateFace(vv3, vv2, vv0);
        }
    }
}
