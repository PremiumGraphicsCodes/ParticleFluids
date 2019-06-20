using PG.Core.Math;

namespace PG.Core.Shape
{
    public class Vertex
    {
        public Vertex(Vector3d position)
        {
            this.Position = position;
            this.Normal = null;
            this.TexCoord = null;
        }

        public Vertex(Vector3d position, Vector3d normal)
        {
            this.Position = position;
            this.Normal = normal;
            this.TexCoord = null;
        }

        public Vertex(Vector3d position, Vector3d normal, Vector2d texCoord)
        {
            this.Position = position;
            this.Normal = normal;
            this.TexCoord = texCoord;
        }

        public Vector3d Position { get; set; }

        public Vector3d Normal { get; set; }

        public Vector2d TexCoord { get; set; }
    }
}
