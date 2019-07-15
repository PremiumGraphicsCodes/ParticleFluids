using PG.Core.Math;

namespace PG.Core.Shape
{
    public class Vertex
    {
        public Vertex(Vector3d position, int id)
        {
            this.Position = position;
            this.Normal = null;
            this.TexCoord = null;
            this.Id = id;
        }

        public Vertex(Vector3d position, Vector3d normal, int id)
        {
            this.Position = position;
            this.Normal = normal;
            this.TexCoord = null;
            this.Id = id;
        }

        public Vertex(Vector3d position, Vector3d normal, Vector2d texCoord, int id)
        {
            this.Position = position;
            this.Normal = normal;
            this.TexCoord = texCoord;
            this.Id = id;
        }

        public Vector3d Position { get; set; }

        public Vector3d Normal { get; set; }

        public Vector2d TexCoord { get; set; }

        public int Id { get; }
    }
}
