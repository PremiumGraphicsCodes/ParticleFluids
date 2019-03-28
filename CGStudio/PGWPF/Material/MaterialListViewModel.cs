using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace PG.CGStudio.Material
{
    public class MaterialItem : BindableBase
    {
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public MaterialItem()
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

    public class MaterialListViewModel
    {
        public ObservableCollection<MaterialItem> Items { get; set; }

        public MaterialListViewModel()
        {
            Items = new ObservableCollection<MaterialItem>();
            var item1 = new MaterialItem();
            item1.Name.Value = "Material1";
            item1.IsVisible.Value = true;
            var item2 = new MaterialItem();
            item2.Name.Value = "Material2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }

    }
}
