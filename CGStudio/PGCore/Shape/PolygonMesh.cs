using PG.Core.Math;
using System.Collections.Generic;

namespace PG.Core.Shape
{
    public class Face
    {
        public Face(Vertex v0, Vertex v1, Vertex v2)
        {
            this.V0 = v0;
            this.V1 = v1;
            this.V2 = v2;
        }

        public Vertex V0 { get; set; }
        public Vertex V1 { get; set; }
        public Vertex V2 { get; set; }
    }

    public class PolygonMesh
    {
        private List<Vertex> vertices;
        private List<Face> faces;

        public List<Vertex> Vertices
        {
            get { return vertices; }
        }

        public List<Face> Faces
        {
            get { return faces; }
        }

        public PolygonMesh(List<Vertex> vertices, List<Face> faces)
        {
            this.vertices = vertices;
            this.faces = faces;
        }
    }
}
