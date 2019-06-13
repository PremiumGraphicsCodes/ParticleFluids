﻿using PG.CGStudio.UICtrl;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Object.Select
{
    public class SelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveCommand PickCommand { get; }

        public List<ObjectModel> SelectedObjects
        {
            get { return Picker.PickedObjects; }
        }

        private ObjectPickUICtrl Picker { get; }

        public SelectViewModel()
        {
            Id = new ReactiveProperty<int>();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
            Picker = new ObjectPickUICtrl(10);
        }

        private void OnPickUI()
        {
            Canvas3d.Instance.UICtrl = Picker;
            Picker.Action = OnPicked;
        }

        private void OnPicked(int id)
        {
            this.Id.Value = id;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            ;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }
    }
}
