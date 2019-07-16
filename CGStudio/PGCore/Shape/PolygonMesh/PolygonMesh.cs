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

        public List<Vector3d> Positions
        {
            get { return positions; }
        }

        public List<Vector3d> Normals
        {
            get { return normals; }
        }

        public List<Vector2d> TexCoords
        {
            get { return texCoords; }
        }

        public VertexFactory()
        {
            nextVertexId = 0;
            positions = new List<Vector3d>();
            normals = new List<Vector3d>();
            texCoords = new List<Vector2d>();
        }

        public void CreatePosition(Vector3d position)
        {
            positions.Add(position);
        }

        public void CreateNormal(Vector3d normal)
        {
            normals.Add(normal);
        }

        public void CreateTexCoord(Vector2d texCoord)
        {
            texCoords.Add(texCoord);
        }

        /*
        public void CreateVertex(int positionId)
        {
            var p = positions[positionId];
            return new Vertex(p, nextVertexId++);
        }
        */
    }

}
