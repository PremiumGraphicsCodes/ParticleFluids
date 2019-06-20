﻿using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class ParticleSystemSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<int> PointId { get; }

        public ReactiveCommand PickCommand { get; }

        public Vector3dViewModel PositionViewModel { get; }

        private ObjectPickUICtrl Picker { get; }

        public ParticleSystemSelectViewModel()
        {
            Id = new ReactiveProperty<int>();
            PointId = new ReactiveProperty<int>();
            PositionViewModel = new Vector3dViewModel();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
            Picker = new ObjectPickUICtrl(10, Core.Shape.ShapeType.ParticleSystem);
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
            var obj = MainModel.Instance.Repository.Objects.FindObjectById(id.parentId);
            this.PositionViewModel.Value = obj.GetPosition(id.childId);
            var sphere = new Sphere3d(1.0, obj.GetPosition(id.childId));
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            MainModel.Instance.Repository.Items.Add(builder.WireFrame, new WireAppearance(),"Item");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl(Canvas3d.Instance.Renderer.camera);
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
