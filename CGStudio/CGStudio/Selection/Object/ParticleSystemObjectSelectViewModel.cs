using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Control.Shape;
using PG.Core;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class ParticleSystemObjectSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<int> PointId { get; }

        public ReactiveCommand PickCommand { get; }

        public ParticleSystemView ParticleSystemView { get; }

        public Vector3dViewModel PositionViewModel { get; }

        private ObjectPickUICtrl Picker { get; }

        public ParticleSystemObjectSelectViewModel()
        {
            Id = new ReactiveProperty<int>();
            PointId = new ReactiveProperty<int>();
            PositionViewModel = new Vector3dViewModel();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
            Picker = new ObjectPickUICtrl(10, Core.Shape.ShapeType.ParticleSystem);
            ParticleSystemView = new ParticleSystemView();
        }

        private void OnPickUI()
        {
            Canvas3d.Instance.UICtrl = Picker;
            Picker.Action = OnPicked;
        }

        private void OnPicked(ObjectId id)
        {
            this.Id.Value = id.parentId;
            this.PointId.Value = id.childId;
            //var obj = MainModel.Instance.Repository.Objects.FindObjectById(id.parentId);
            //this.PositionViewModel.Value = obj.GetPosition(id.childId);
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
