using PG.Core.Math;

namespace PG.Core.Shape
{
    public class Vertex
    {
        public Vertex(Vector3d position)
        {
            this.Position = position;
        }

        public Vector3d Position { get; set; }
    }
}
