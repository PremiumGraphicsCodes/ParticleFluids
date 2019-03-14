using PG.Core.Math;

namespace PG.Core.Graphics
{
    public struct PointLight
    {
        public ColorRGB Ambient { get; set; }
        public ColorRGB Diffuset { get; set; }
        public ColorRGB Specular { get; set; }
        public Vector3d Position { get; set; }
    }
}
