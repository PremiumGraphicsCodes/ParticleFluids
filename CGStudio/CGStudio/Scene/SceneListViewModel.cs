using PG.Core;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio
{
    public class SceneListViewModel
    {
        public List<Scene> Items { get; }

        public SceneListViewModel()
        {
            //Items = MainModel.Instance.Repository.Scene;
            Items = new List<Scene>();
            Items.Add(MainModel.Instance.Repository.Scene);
            /*
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
