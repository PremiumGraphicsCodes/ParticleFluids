using PG.Core.Graphics;
using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace PG.CGStudio.Light
{
    public class LightListViewModel
    {
        public ObservableCollection<PointLight> Items { get; set; }

        public LightListViewModel()
        {
            Items = new ObservableCollection<PointLight>();
            var item1 = new PointLight(1);
            item1.Name.Value = "Light1";
            item1.IsVisible.Value = true;
            var item2 = new PointLight(2);
            item2.Name.Value = "Light2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }

    }
}
