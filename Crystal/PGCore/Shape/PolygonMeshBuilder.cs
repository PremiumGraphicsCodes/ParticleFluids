using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class PolygonMeshBuilder
    {
        private List<Triangle3d> triangles;

        public PolygonMeshBuilder()
        {
            this.triangles = new List<Triangle3d>();
        }

        public PolygonMesh PolygonMesh
        {
            get { return new PolygonMesh(triangles); }
        }

        public void Build(Box3d box)
        {
            var vertices = new List<Vector3d>();
        }

        public void Build(Sphere3d sphere, int u, int v)
        {
            var vertices = new Vector3d[u, v];
            for (int i = 0; i < u; ++i)
            {
                var uu = u / (double)i;
                for (int j = 0; j < v; ++j)
                {
                    var vv = j / (double)v;
                    vertices[u, v] = sphere.GetPosition(u, v);
                }
            }

            for(int i = 0; i < u-1; ++i)
            {
                for(int j = 0; j < v-1; ++j)
                {
                    var v1 = vertices[i, j];
                    var v2 = vertices[i + 1, j];
                    var v3 = vertices[i, j + 1];
                    var triangle = new Triangle3d(v1, v2, v3);
                    triangles.Add(triangle);
                }
            }
        }

    }
}
