namespace PG.Core.Graphics
{
    public struct Material
    {
        public ColorRGB Ambient { get; set; }
        public ColorRGB Diffuse { get; set; }
        public ColorRGB Specular { get; set; }
        public float Shininess { get; set; }
    }
}
