using PG.Core.Math;

namespace PG.Core.Shape
{
    public class Vertex
    {
        public Vertex(int positionId, int id) :
            this(positionId, -1, -1, id)
        {
        }

        public Vertex(int position, int normal, int id) :
            this(position, normal, -1, id)
        {
        }

        public Vertex(int position, int normal, int texCoordId, int id)
        {
            this.PositionId = position;
            this.NormalId = normal;
            this.TexCoordId = texCoordId;
            this.Id = id;
        }

        public int PositionId { get; set; }

        public int NormalId { get; set; }

        public int TexCoordId { get; set; }

        public int Id { get; }
    }
}
