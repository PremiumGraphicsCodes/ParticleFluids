using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace PG.CGStudio.Light
{
    public class LightItem : BindableBase
    {
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public LightItem()
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

    public class LightListViewModel
    {
        public ObservableCollection<LightItem> Items { get; set; }

        public LightListViewModel()
        {
            Items = new ObservableCollection<LightItem>();
            var item1 = new LightItem();
            item1.Name.Value = "Light1";
            item1.IsVisible.Value = true;
            var item2 = new LightItem();
            item2.Name.Value = "Light2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }

    }
}
