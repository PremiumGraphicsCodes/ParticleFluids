using PG.Core.Math;
using System.Collections.Generic;

namespace PG.Core.Shape
{
    public class PolygonMesh
    {
        private List<Triangle3d> triangles;

        public List<Triangle3d> Triangles
        {
            get { return triangles; }
        }

        public PolygonMesh(List<Triangle3d> triangles)
        {
            this.triangles = triangles;
        }
    }
}
