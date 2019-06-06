using Reactive.Bindings;
using System;

namespace PG.Core.Graphics
{
    public class Material
    {
        public ColorRGBA Ambient { get; set; }
        public ColorRGBA Diffuse { get; set; }
        public ColorRGBA Specular { get; set; }
        public float Shininess { get; set; }
    }
}
