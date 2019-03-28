using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.ObjectModel;

namespace PG.CGStudio
{
    public class TreeSource : BindableBase
    {
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public TreeSource()
        {
            Name = new ReactiveProperty<string>();
            IsVisible = new ReactiveProperty<bool>();
        }
    }

    public class ObjectListViewModel
    {
        public ObservableCollection<TreeSource> TreeRoot { get; set; }

        public ObjectListViewModel()
        {
            TreeRoot = new ObservableCollection<TreeSource>();
            var item1 = new TreeSource();
            item1.Name.Value = "Object1";
            item1.IsVisible.Value = true;
            var item2 = new TreeSource();
            item2.Name.Value = "Object2";
            item2.IsVisible.Value = false;
            TreeRoot.Add(item1);
            TreeRoot.Add(item2);
        }
    }
}
