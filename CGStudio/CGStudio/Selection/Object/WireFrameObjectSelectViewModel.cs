using PG.CGStudio.UICtrl;
using PG.Core;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Selection.Object
{
    public class WireFrameObjectSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<int> EdgeId { get; }

        public ReactiveCommand PickCommand { get; }

        public WireFrameObjectSelectViewModel()
        {
            Id = new ReactiveProperty<int>();
            EdgeId = new ReactiveProperty<int>();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new ObjectPickUICtrl(10, Core.Shape.ShapeType.WireFrame);
            picker.Action = OnPicked;
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            this.Id.Value = id.parentId;
            this.EdgeId.Value = id.childId;
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
            ;
        }
    }
}
