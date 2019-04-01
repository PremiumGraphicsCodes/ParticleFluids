using PG.Core.Math;
using Reactive.Bindings;
using System;

namespace PG.Core.Graphics
{
    public class PointLight
    {
        public int ID { get; }

        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public PointLight(int id)
        {
            this.ID = id;
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
        public ColorRGBA Diffuset { get; set; }
        public ColorRGBA Specular { get; set; }
        public Vector3d Position { get; set; }
    }
}
