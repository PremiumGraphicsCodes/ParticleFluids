using PG.CGStudio.UICtrl;
using PG.Core;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Object.Select
{
    public class SceneSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        private PickUICtrl Picker { get; }

        public SceneSelectViewModel()
        {
            PickCommand.Subscribe(OnPickUI);
            Picker = new PickUICtrl(10, Core.SceneType.AllScene);
            Picker.Action = OnPicked;
        }

        private void OnPickUI()
        {
            Canvas3d.Instance.UICtrl = Picker;
            Picker.Action = OnPicked;
        }

        private void OnPicked(ObjectId id)
        {
            this.Id.Value = id.parentId;
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
