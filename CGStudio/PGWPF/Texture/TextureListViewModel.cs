using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Texture
{
    public class TextureItem : BindableBase
    {
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public TextureItem()
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

    public class TextureListViewModel
    {
        public ObservableCollection<TextureItem> Items { get; set; }

        public TextureListViewModel()
        {
            Items = new ObservableCollection<TextureItem>();
            var item1 = new TextureItem();
            item1.Name.Value = "Texture1";
            item1.IsVisible.Value = true;
            var item2 = new TextureItem();
            item2.Name.Value = "Texture2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }
    }
}
