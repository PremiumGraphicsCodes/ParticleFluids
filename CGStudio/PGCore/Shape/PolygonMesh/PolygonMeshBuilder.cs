﻿using System.Collections.Generic;
using PG.Core.Math;

namespace PG.Core.Shape
{
    public class PolygonMeshBuilder
    {
        private List<Vertex> vertices;

        private List<PolygonFace> faces;

        private int nextVertexId;

        public PolygonMeshBuilder()
        {
            this.vertices = new List<Vertex>();
            this.faces = new List<PolygonFace>();
            this.nextVertexId = 0;
        }

        public PolygonMesh PolygonMesh
        {
            get { return new PolygonMesh(vertices, faces); }
        }

        public void Build(Box3d box)
        {
            var vertices = new List<Vertex>();
        }

        public void Build(Sphere3d sphere, int u, int v)
        {
            var vertices = new Vertex[u, v];
            for (int i = 0; i < u; ++i)
            {
                var uu = u / (double)i;
                for (int j = 0; j < v; ++j)
                {
                    var vv = j / (double)v;
                    var p = sphere.GetPosition(1.0, u, v);
                    var n = sphere.GetNormal(u, v);
                    var t = new Vector2d(uu, vv);
                    vertices[u, v] = new Vertex(p, n, t, nextVertexId++);
                }
            }

            for(int i = 0; i < u-1; ++i)
            {
                for(int j = 0; j < v-1; ++j)
                {
                    var v1 = vertices[i, j].Id;
                    var v2 = vertices[i + 1, j].Id;
                    var v3 = vertices[i, j + 1].Id;
                    var f = new PolygonFace(v1, v2, v3);
                    faces.Add(f);
                }
            }
        }

        public void Build(Cylinder3d cylinder, int u, int v)
        {
            var vertices = new Vertex[u, v];
            for (int i = 0; i < u; ++i)
            {
                var uu = u / (double)i;
                for (int j = 0; j < v; ++j)
                {
                    var vv = j / (double)v;
                    vertices[u, v] = new Vertex( cylinder.GetPosition(1.0, u, v), nextVertexId++ );
                }
            }

            for (int i = 0; i < u - 1; ++i)
            {
                for (int j = 0; j < v - 1; ++j)
                {
                    var v1 = vertices[i, j].Id;
                    var v2 = vertices[i + 1, j].Id;
                    var v3 = vertices[i, j + 1].Id;
                    var face = new PolygonFace(v1, v2, v3);
                    faces.Add(face);
                }
            }
        }
    }
}
