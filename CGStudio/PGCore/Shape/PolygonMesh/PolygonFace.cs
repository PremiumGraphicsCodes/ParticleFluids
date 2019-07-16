namespace PG.Core.Shape
{
    public class PolygonFace
    {
        public PolygonFace(int v0, int v1, int v2, int id)
        {
            this.V0 = v0;
            this.V1 = v1;
            this.V2 = v2;
            this.Id = id;
        }

        public int V0 { get; set; }
        public int V1 { get; set; }
        public int V2 { get; set; }
        public int Id { get; }
    }
}
