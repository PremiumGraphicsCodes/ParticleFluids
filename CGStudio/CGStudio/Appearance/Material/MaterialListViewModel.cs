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
        public ObservableCollection<MaterialModel> Items { get; }

        public ReactiveCommand AddCommand { get; }

        public ReactiveCommand EditCommand { get; }

        public ReactiveCommand DeleteCommand { get; }

        public MaterialListViewModel()
        {
//            Items = MainModel.Instance.Repository.Material.Items;

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
