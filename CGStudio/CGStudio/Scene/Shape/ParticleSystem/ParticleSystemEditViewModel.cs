﻿using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.ParticleSystem
{
    public class ParticleSystemEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public ReactiveCommand EditCommand { get; }
            = new ReactiveCommand();

        public ParticleSystemEditViewModel()
        {
            EditCommand.Subscribe(OnEdit);
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["ParticleSystemEdit"] as PG.Core.Scene;
            if (item == null)
            {
                return;
            }
            Id.Value = item.Id;
            Name.Value = item.Name;
        }

        private void OnEdit()
        {
            MainModel.Instance.Repository.ChangeName(Id.Value, Name.Value);
        }
    }
}
