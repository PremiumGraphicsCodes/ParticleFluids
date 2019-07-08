using Reactive.Bindings;

namespace PG.CGStudio
{
    public class SceneListViewModel
    {
        public ReadOnlyReactiveCollection<ObjectModel> Items { get; }

        public SceneListViewModel()
        {
            /*
            //Items = MainModel.Instance.Repository.Objects.Objects.ToReadOnlyReactiveCollection();
//            var model = 
            Items = new ObservableCollection<ObjectItem>();
            var item1 = new ObjectItem();
            item1.Name.Value = "Object1";
            item1.IsVisible.Value = true;
            var item2 = new ObjectItem();
            item2.Name.Value = "Object2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
            */
        }
    }
}
