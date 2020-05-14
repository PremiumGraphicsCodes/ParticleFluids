using PG.CGStudio.UICtrl;
using PG.Core;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Object.Select
{
    public class ShapeSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public PickUICtrl Picker { get; }

        public ShapeSelectViewModel()
        {
            PickCommand.Subscribe(OnPickUI);
            Picker = new PickUICtrl(10, Core.SceneType.AllScene);
            Picker.AddAction( OnPicked );
        }

        private void OnPickUI()
        {
            HwndHostPresenter3d.Instance.Canvas.UICtrl = Picker;
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
