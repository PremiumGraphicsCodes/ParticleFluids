using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.Core.Graphics
{
    public class Texture
    {
        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public string ImagePath { get; set; }

        public Texture()
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
