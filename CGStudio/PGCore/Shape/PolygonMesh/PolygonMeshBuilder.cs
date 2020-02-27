using PG.Core.Math;
using System.Collections.Generic;

namespace PG.Core.Shape
{
    public class PolygonMeshBuilder
    {
        private readonly List<Vector3d> positions = new List<Vector3d>();
        private readonly List<Vector3d> normals = new List<Vector3d>();
        private readonly List<Vector2d> texCoords = new List<Vector2d>();
        private readonly List<Vertex> vertices = new List<Vertex>();
        private readonly List<PolygonFace> faces = new List<PolygonFace>();
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

        public PolygonMesh ToPolygonMesh()
        {
            var polygon = new PolygonMesh
            {
                Positions = positions,
                Normals = normals,
                TexCoords = texCoords,
                Vertices = vertices,
                Faces = faces
            };
            return polygon;
        }

        public void Add(Ellipse3d ellipse, int unum)
        {
            var normal = CreateNormal(ellipse.Normal());

            // create center
            var centerPosition = CreatePosition(ellipse.Center);
            var centerTexCoord = CreateTexCoord(new Vector2d(0, 0));
            var centerVertex = CreateVertex(centerPosition, normal, centerTexCoord);

            // create outer.
            var positions = new CircularBuffer1d<int>(unum, 0);
            var texCoords = new CircularBuffer1d<int>(unum, 0);
            for (int i = 0; i < unum; ++i)
            {
                var u = i / (double)(unum);
                positions[i] = CreatePosition(ellipse.GetPosition(u));
                texCoords[i] = CreateTexCoord(new Vector2d(1.0, u));
            }

            var vertices = new CircularBuffer1d<int>(unum, 0);
            for (int i = 0; i < unum; ++i)
            {
                vertices[i] = CreateVertex(positions[i], normal, texCoords[i]);
            }

            // create faces.
            var faces = new CircularBuffer1d<int>(unum, 0);
            for (int i = 0; i < unum; ++i)
            {
                faces[i] = CreateFace(centerVertex, vertices[i], vertices[i+1]);
            }
        }

        /*
        public void Add(Circle3d circle, int unum)
        {
            var positions = new CircularBuffer1d<int>(unum, 0);
            for(int i = 0; i < unum; ++i)
            {
                var u = i / (double)(unum);
                positions[i] = CreatePosition( circle.GetPosition(i) );
            }
//            var normal = CreateNormal( circle.N)
        }
        */



        public void Add(Box3d box)
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

        public void Add(Sphere3d sphere, int u, int v)
        {
            var vertices = new int[u+1, v+1];
            for (int i = 0; i <= u; ++i)
            {
                var uu = i / (double)u;
                for (int j = 0; j <= v; ++j)
                {
                    var vv = j / (double)v;
                    var p = CreatePosition(sphere.GetPosition(1.0, uu, vv));
                    var n = CreateNormal(sphere.GetNormal(uu, vv));
                    var t = CreateTexCoord(new Vector2d(uu, vv));
                    vertices[i, j] = CreateVertex(p, n, t);
                }
            }

            for (int i = 0; i < u; ++i)
            {
                for (int j = 0; j < v; ++j)
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

        public void Add(Cylinder3d cylinder, int unum)
        {
            // create bottom
            var bottomVertices = new CircularBuffer1d<int>(unum, 0);

            var bottomPosition = CreatePosition(cylinder.GetPosition(0.0, 0.0, 0.0));
            var bottomNormal = CreateNormal(new Vector3d(0.0, -1.0, 0.0));
            var bottomTexCoord = CreateTexCoord(new Vector2d(0.0, 0.0));
            var bottomVertex = CreateVertex(bottomPosition, bottomNormal, bottomTexCoord);

            for (int i = 0; i < unum; ++i)
            {
                var uu = i / (double)unum;
                var p = CreatePosition(cylinder.GetPosition(1.0, uu, 0.0));
                var n = CreateNormal(cylinder.GetNormal(uu, 0.0));
                var t = CreateTexCoord(new Vector2d(uu, 0.0));
                bottomVertices[i] = CreateVertex(p, n, t);
            }

            for (int i = 0; i < unum; ++i)
            {
                CreateFace(bottomVertex, bottomVertices[i], bottomVertices[i + 1]);
            }

            // create top
            var topVertices = new CircularBuffer1d<int>(unum, 0);

            var topPosition = CreatePosition( cylinder.GetPosition(0.0, 0.0, 1.0) );
            var topNormal = CreateNormal(new Vector3d(0.0, 1.0, 0.0));
            var topTexCoord = CreateTexCoord(new Vector2d(0.0, 0.0));
            var topVertex = CreateVertex(topPosition, topNormal, topTexCoord);

            for (int i = 0; i < unum; ++i)
            {
                var uu = i / (double)unum;
                var p = CreatePosition(cylinder.GetPosition(1.0, uu, 1.0));
                var n = CreateNormal(cylinder.GetNormal(uu, 1.0));
                var t = CreateTexCoord(new Vector2d(uu, 1.0));
                topVertices[i] = CreateVertex(p, n, t);
            }

            for (int i = 0; i < unum; ++i)
            {
                CreateFace(topVertex, topVertices[i], topVertices[i + 1]);
            }

            for (int i = 0; i < unum; ++i)
            {
                CreateFace(bottomVertices[i], bottomVertices[i + 1], topVertices[i]);
                CreateFace(topVertices[i + 1], topVertices[i], bottomVertices[i+1]);
            }
        }

        private void Add(int v0, int v1, int v2, int v3)
        {
            var p0 = positions[v0];
            var p1 = positions[v1];
            var p2 = positions[v2];

            var normal = (p1 - p0).Cross(p2 - p0);
            var n0 = CreateNormal(normal);

            var t0 = CreateTexCoord(new Vector2d(0.0, 0.0));
            var t1 = CreateTexCoord(new Vector2d(1.0, 0.0));
            var t2 = CreateTexCoord(new Vector2d(1.0, 1.0));
            var t3 = CreateTexCoord(new Vector2d(0.0, 1.0));

            var vv0 = CreateVertex(v0, n0, t0);
            var vv1 = CreateVertex(v1, n0, t1);
            var vv2 = CreateVertex(v2, n0, t2);
            var vv3 = CreateVertex(v3, n0, t3);

            CreateFace(vv0, vv1, vv2);
            CreateFace(vv3, vv2, vv0);
        }

        private int CreatePosition(Vector3d position)
        {
            positions.Add(position);
            return positions.Count - 1;
        }

        private int CreateNormal(Vector3d normal)
        {
            normals.Add(normal);
            return normals.Count - 1;
        }

        private int CreateTexCoord(Vector2d texCoord)
        {
            texCoords.Add(texCoord);
            return texCoords.Count - 1;
        }

        private int CreateVertex(int positionId, int normalId, int texCoordId)
        {
            var v = new Vertex(positionId, normalId, texCoordId, nextVertexId++);
            vertices.Add(v);
            return v.Id;
        }

        private int CreateFace(int v0, int v1, int v2)
        {
            var f = new PolygonFace(v0, v1, v2, nextFaceId++);
            faces.Add(f);
            return f.Id;
        }
    }
}
