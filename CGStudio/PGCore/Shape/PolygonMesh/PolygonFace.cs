namespace PG.Core.Shape
{
    public class PolygonFace
    {
        public PolygonFace(Vertex v0, Vertex v1, Vertex v2)
        {
            this.V0 = v0;
            this.V1 = v1;
            this.V2 = v2;
        }

        public Vertex V0 { get; set; }
        public Vertex V1 { get; set; }
        public Vertex V2 { get; set; }
    }

}
