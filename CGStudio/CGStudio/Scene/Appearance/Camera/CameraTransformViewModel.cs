using PG.Control.Math;
using PG.Core.Math;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Scene.Appearance
{
    public class CameraTransformViewModel
    {
        public Vector3dViewModel EyePositionViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel TargetPositionViewModel { get; }
            = new Vector3dViewModel();

        public Matrix4dViewModel RotationMatrixViewModel { get; }
            = new Matrix4dViewModel();

        public ReactiveCommand ApplyCommand { get; }
            = new ReactiveCommand();

        public CameraTransformViewModel()
        {
            var model = MainModel.Instance;
            EyePositionViewModel.Value = PG.CLI.Command.Get<Vector3d>(model.World.Adapter, PG.GetLabels.CameraEyePositionLabel);
            TargetPositionViewModel.Value = PG.CLI.Command.Get<Vector3d>(model.World.Adapter, PG.GetLabels.CameraTargetPositionLabel);
            RotationMatrixViewModel.Value = PG.CLI.Command.Get<Matrix4d>(model.World.Adapter, PG.GetLabels.CameraRotationMatrixLabel);

            ApplyCommand.Subscribe(OnApply);
        }

        private void OnApply()
        {

        }
    }
}
