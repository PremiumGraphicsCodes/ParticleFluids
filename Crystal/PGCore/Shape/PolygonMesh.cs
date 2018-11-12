using PG.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Shape
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
