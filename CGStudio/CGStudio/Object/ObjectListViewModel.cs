using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.ObjectModel;

namespace PG.CGStudio
{
    public class ObjectItem : BindableBase
    {
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public ObjectItem()
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

    public class ObjectListViewModel
    {
        public ObservableCollection<ObjectItem> Items { get; set; }

        public ObjectListViewModel()
        {
            Items = new ObservableCollection<ObjectItem>();
            var item1 = new ObjectItem();
            item1.Name.Value = "Object1";
            item1.IsVisible.Value = true;
            var item2 = new ObjectItem();
            item2.Name.Value = "Object2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }
    }
}
