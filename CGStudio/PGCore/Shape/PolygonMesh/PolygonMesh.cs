using System.Collections.Generic;
using PG.Core.Math;

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

    public class VertexFactory
    {
        private int nextVertexId;
        private List<Vector3d> positions;
        private List<Vector3d> normals;
        private List<Vector2d> texCoords;

        VertexFactory()
        {
            nextVertexId = 0;
            positions = new List<Vector3d>();
            texCoords = new List<Vector2d>();
        }

        void CreatePosition(Vector3d position)
        {
            positions.Add(position);
        }

        void CreateNormal(Vector3d normal)
        {
            normals.Add(normal);
        }

        void CreateTexCoord(Vector2d texCoord)
        {
            texCoords.Add(texCoord);
        }
    }

}
