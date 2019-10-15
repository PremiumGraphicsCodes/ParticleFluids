﻿using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class SphereRegionSelectViewModel : BindableBase
    {
        public ShapeSelectViewModel SelectViewModel { get; }
            = new ShapeSelectViewModel();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public SphereRegionSelectViewModel()
        {
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new PickUICtrl(10, SceneType.AllScene)
            {
                Action = OnPicked
            };
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            var model = MainModel.Instance.Repository.Adapter;
            var position = PG.CLI.Command.Get(model, PG.GetLabels.PositionLabel, id.parentId, id.childId) as Vector3d;
            /*
            command.SetArg(, id.parentId);
            command.SetArg("ChildId", id.childId);
            command.Execute(MainModel.Instance.Repository.Adapter);
            var position = command.GetResult<Vector3d>("Position");
            command.Clear();
                        */

            var sphere = new Sphere3d(SphereViewModel.Value.Radius, position);
            SphereViewModel.Value = sphere;
            var builder = new WireFrameBuilder();
            builder.Build(sphere, 24, 24);
            var appearance = new WireAppearance();

            var command = new PG.CLI.Command();
            command.Create(PG.WireFrameAddLabels.WireFrameAddLabel);
            command.SetArg(PG.WireFrameAddLabels.LinesLabel, builder.WireFrame);
            command.SetArg(PG.WireFrameAddLabels.IsItemLabel, true);
            command.Execute(MainModel.Instance.Repository.Adapter);

            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
