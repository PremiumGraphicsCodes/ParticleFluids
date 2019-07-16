using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class PolygonMesh
    {
        private List<Vertex> vertices;
        private List<PolygonFace> faces;
        private List<Vector3d> positions;
        private List<Vector3d> normals;
        private List<Vector2d> texCoords;
        private int nextVertexId;

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

        public List<Vertex> Vertices
        {
            get { return vertices; }
        }

        public List<PolygonFace> Faces
        {
            get { return faces; }
        }

        public PolygonMesh()
        {
            this.positions = new List<Vector3d>();
            this.normals = new List<Vector3d>();
            this.texCoords = new List<Vector2d>();
            this.vertices = new List<Vertex>();
            this.faces = new List<PolygonFace>();
            this.nextVertexId = 0;
        }

        public int CreatePosition(Vector3d position)
        {
            positions.Add(position);
            return positions.Count - 1;
        }

        public int CreateNormal(Vector3d normal)
        {
            normals.Add(normal);
            return normals.Count - 1;
        }

        public int CreateTexCoord(Vector2d texCoord)
        {
            texCoords.Add(texCoord);
            return texCoords.Count - 1;
        }

        public int CreateVertex(int positionId, int normalId, int texCoordId)
        {
            var v = new Vertex(positionId, normalId, texCoordId, nextVertexId++);
            vertices.Add(v);
            return v.Id;
        }
    }
}
