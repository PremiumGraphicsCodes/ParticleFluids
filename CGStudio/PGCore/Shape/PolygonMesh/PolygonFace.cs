namespace PG.Core.Shape
{
    public class PolygonFace
    {
        public PolygonFace(int v0, int v1, int v2)
        {
            this.V0 = v0;
            this.V1 = v1;
            this.V2 = v2;
        }

        public int V0 { get; set; }
        public int V1 { get; set; }
        public int V2 { get; set; }
    }
}
