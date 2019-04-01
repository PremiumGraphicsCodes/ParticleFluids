using Reactive.Bindings;
using System;

namespace PG.Core.Graphics
{
    public class Material
    {
        public int ID { get; }
        public ColorRGBA Ambient { get; set; }
        public ColorRGBA Diffuse { get; set; }
        public ColorRGBA Specular { get; set; }
        public float Shininess { get; set; }

        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public Material(int id)
        {
            this.ID = id;
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
