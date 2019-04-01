using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace PG.CGStudio.Material
{

    public class MaterialListViewModel
    {
        public ObservableCollection<PG.Core.Graphics.Material> Items { get; set; }

        public MaterialListViewModel()
        {
            Items = new ObservableCollection<PG.Core.Graphics.Material>();
            var item1 = new PG.Core.Graphics.Material();
            item1.Name.Value = "Material1";
            item1.IsVisible.Value = true;
            var item2 = new PG.Core.Graphics.Material();
            item2.Name.Value = "Material2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }

    }
}
