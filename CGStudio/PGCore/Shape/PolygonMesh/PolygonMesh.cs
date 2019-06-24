using PG.Core.Math;
using System.Collections.Generic;

namespace PG.Core.Shape
{
    public class PolygonMesh
    {
        private List<Vertex> vertices;
        private List<PolygonFace> faces;

        public List<Vertex> Vertices
        {
            get { return vertices; }
        }

        public List<PolygonFace> Faces
        {
            get { return faces; }
        }

        public PolygonMesh(List<Vertex> vertices, List<PolygonFace> faces)
        {
            this.vertices = vertices;
            this.faces = faces;
        }
    }
}
