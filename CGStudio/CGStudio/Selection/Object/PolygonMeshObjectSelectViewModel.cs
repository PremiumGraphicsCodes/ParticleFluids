using PG.CGStudio.UICtrl;
using PG.Control.Graphics;
using PG.Core;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Selection.Object
{
    public class PolygonMeshObjectSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<int> FaceId { get; }

        public ReactiveProperty<int> FaceGroupId { get; }

        public MaterialViewModel MaterialViewModel { get; }

        public ReactiveCommand PickCommand { get; }

        private ObjectPickUICtrl Picker { get; }

        public PolygonMeshObjectSelectViewModel()
        {
            Id = new ReactiveProperty<int>();
            FaceId = new ReactiveProperty<int>();
            FaceGroupId = new ReactiveProperty<int>();
            MaterialViewModel = new MaterialViewModel();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
            Picker = new ObjectPickUICtrl(10, SceneType.PolygonMesh);
        }

        private void OnPickUI()
        {
            Canvas3d.Instance.UICtrl = Picker;
            Picker.Action = OnPicked;
        }

        private void OnPicked(ObjectId id)
        {
            /*
            this.Id.Value = id.parentId;
            this.FaceId.Value = id.childId;
            var obj = MainModel.Instance.Repository.Objects.PolygonMeshes.FindObjectById(id.parentId);
            var attributeId = obj.GetAttributeByFaceId(id.childId);
            var material = MainModel.Instance.Repository.Material.FindObjectById(attributeId);
            this.MaterialViewModel.Value = material.Material;
            //this.PositionViewModel.Value = obj.GetPosition(id.childId);
            */
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
