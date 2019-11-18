using PG.Core.Math;
using System.Collections.Generic;

namespace PG.Core.Shape
{
    public class PolygonMeshBuilder
    {
        private List<Vector3d> positions = new List<Vector3d>();
        private List<Vector3d> normals = new List<Vector3d>();
        private List<Vector2d> texCoords = new List<Vector2d>();
        private List<Vertex> vertices = new List<Vertex>();
        private List<PolygonFace> faces = new List<PolygonFace>();
        private int nextVertexId = 0;
        private int nextFaceId = 0;

        public IEnumerable<Vector3d> Positions { get { return positions; } }

        public IEnumerable<Vector3d> Normals { get { return normals; } }

        public IEnumerable<Vector2d> TexCoords { get { return texCoords; } }

        public IEnumerable<Vertex> Vertices {  get { return vertices; } }

        public IEnumerable<PolygonFace> Faces {  get { return faces; } }

        public PolygonMeshBuilder()
        {
        }

        public void Build(Box3d box)
        {
            var p0 = CreatePosition(box.GetPosition(0, 0, 0));
            var p1 = CreatePosition(box.GetPosition(1, 0, 0));
            var p2 = CreatePosition(box.GetPosition(1, 1, 0));
            var p3 = CreatePosition(box.GetPosition(0, 1, 0));

            var p4 = CreatePosition(box.GetPosition(0, 0, 1));
            var p5 = CreatePosition(box.GetPosition(1, 0, 1));
            var p6 = CreatePosition(box.GetPosition(1, 1, 1));
            var p7 = CreatePosition(box.GetPosition(0, 1, 1));

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
                    var p = CreatePosition(sphere.GetPosition(1.0, uu, vv));
                    var n = CreateNormal(sphere.GetNormal(uu, vv));
                    var t = CreateTexCoord(new Vector2d(uu, vv));
                    vertices[i, j] = CreateVertex(p, n, t);
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
                    CreateFace(v1, v2, v3);
                    CreateFace(v4, v3, v2);
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
                    var p = CreatePosition(cylinder.GetPosition(1.0, uu, vv));
                    var n = CreateNormal(cylinder.GetNormal(uu, vv));
                    vertices[i, j] = CreateVertex(p, n, -1);
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
                    CreateFace(v1, v2, v3);
                    CreateFace(v4, v3, v2);
                }
            }
        }

        private void Add(int v0, int v1, int v2, int v3)
        {
            var p0 = positions[v0];
            var p1 = positions[v1];
            var p2 = positions[v2];

            var normal = (p1 - p0).Cross(p2 - p0);
            var n0 = CreateNormal(normal);

            var vv0 = CreateVertex(v0, n0);
            var vv1 = CreateVertex(v1, n0);
            var vv2 = CreateVertex(v2, n0);
            var vv3 = CreateVertex(v3, n0);

            CreateFace(vv0, vv1, vv2);
            CreateFace(vv3, vv2, vv0);
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

        public int CreateVertex(int positionId, int normalId)
        {
            var v = new Vertex(positionId, normalId, -1, nextVertexId++);
            vertices.Add(v);
            return v.Id;
        }

        public int CreateVertex(int positionId, int normalId, int texCoordId)
        {
            var v = new Vertex(positionId, normalId, texCoordId, nextVertexId++);
            vertices.Add(v);
            return v.Id;
        }

        public int CreateFace(int v0, int v1, int v2)
        {
            var f = new PolygonFace(v0, v1, v2, nextFaceId++);
            faces.Add(f);
            return f.Id;
        }
    }
}
