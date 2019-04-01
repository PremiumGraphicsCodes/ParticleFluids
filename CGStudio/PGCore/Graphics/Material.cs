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

        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public Material()
        {
            Name = new ReactiveProperty<string>();
            IsVisible = new ReactiveProperty<bool>();
            IsVisible.Subscribe(VisibleChanged);
        }

        private void VisibleChanged(bool b)
        {
            System.Diagnostics.Debug.Write(b.ToString());
        }
    }
}
