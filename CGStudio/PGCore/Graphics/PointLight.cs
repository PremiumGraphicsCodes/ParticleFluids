using PG.Core.Math;

namespace PG.Core.Graphics
{
    public struct PointLight
    {
        public ColorRGBA Ambient { get; set; }
        public ColorRGBA Diffuset { get; set; }
        public ColorRGBA Specular { get; set; }
        public Vector3d Position { get; set; }
    }
}
