using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class PolygonMesh
    {
        public List<Vector3d> Positions { get; set; }

        public List<Vector3d> Normals { get; set; }

        public List<Vector2d> TexCoords { get; set; }

        public List<Vertex> Vertices { get; set; }

        public List<PolygonFace> Faces { get; set; }

        public PolygonMesh()
        {
            this.Positions = new List<Vector3d>();
            this.Normals = new List<Vector3d>();
            this.TexCoords = new List<Vector2d>();
            this.Vertices = new List<Vertex>();
            this.Faces = new List<PolygonFace>();
        }
    }
}
