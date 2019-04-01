using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;

namespace PG.CGStudio.Material
{

    public class MaterialListViewModel
    {
        public ObservableCollection<PG.Core.Graphics.Material> Items { get; set; }

        public ReactiveCommand AddCommand { get; }

        public ReactiveCommand EditCommand { get; }

        public ReactiveCommand DeleteCommand { get; }

        public MaterialListViewModel()
        {
            Items = new ObservableCollection<PG.Core.Graphics.Material>();
            var item1 = new PG.Core.Graphics.Material(1);
            item1.Name.Value = "Material1";
            item1.IsVisible.Value = true;
            var item2 = new PG.Core.Graphics.Material(2);
            item2.Name.Value = "Material2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);

            AddCommand = new ReactiveCommand();
            AddCommand.Subscribe(OnAdd);
            EditCommand = new ReactiveCommand();
            DeleteCommand = new ReactiveCommand();
        }

        private void OnAdd()
        {
            MessageBox.Show("Add");
        }
    }
}
