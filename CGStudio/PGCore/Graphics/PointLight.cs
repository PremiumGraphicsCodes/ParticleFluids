using PG.Core.Math;
using Reactive.Bindings;
using System;

namespace PG.Core.Graphics
{
    public class PointLight
    {
        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public PointLight()
        {
            Name = new ReactiveProperty<string>();
            IsVisible = new ReactiveProperty<bool>();
            IsVisible.Subscribe(VisibleChanged);
            this.Position = new Vector3d(0, 0, 0);
        }

        private void VisibleChanged(bool b)
        {
            System.Diagnostics.Debug.Write(b.ToString());
        }

        public ColorRGBA Ambient { get; set; }
        public ColorRGBA Diffuse { get; set; }
        public ColorRGBA Specular { get; set; }
        public Vector3d Position { get; set; }
    }
}
