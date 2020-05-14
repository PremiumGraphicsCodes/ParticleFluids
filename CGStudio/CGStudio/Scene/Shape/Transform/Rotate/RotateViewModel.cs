﻿using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using Reactive.Bindings;
using System;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class RotateViewModel
    {
        public Vector3dViewModel AngleViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel CenterViewModel { get; }
            = new Vector3dViewModel();

        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        public RotateViewModel()
        {
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.ShapeSelectViewModel.Picker.AddAction(OnSelected);
        }

        private void OnSelected(ObjectId id)
        {
            if (id.parentId == 0)
            {
                return;
            }

            var center = World.Instance.Scenes.GetCenter(id.parentId);
            CenterViewModel.Value = center;
            HwndHostPresenter3d.Instance.Canvas.UICtrl = new RotateUICtrl(this);
        }


        private void OnOk()
        {
            World.Instance.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            OnCancel();

            World.Instance.Scenes.Clear(0);
            World.Instance.Scenes.ShowBoundingBox(ShapeSelectViewModel.Id.Value);
        }

        private void OnCancel()
        {
            World.Instance.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, Matrix4d.Identity());
            var canvas = HwndHostPresenter3d.Instance;
            canvas.Update(World.Instance);
            canvas.Render();

            AngleViewModel.Value = new Vector3d(0, 0, 0);
        }

        public void SetMatrix(bool doRender)
        {
            World.Instance.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                var canvas = HwndHostPresenter3d.Instance;
                canvas.Update(World.Instance);
                canvas.Render();
            }
        }

        public void Transform(bool doRender)
        {
            World.Instance.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                var canvas = HwndHostPresenter3d.Instance;
                canvas.Update(World.Instance);
                canvas.Render();
            }
        }

        public Matrix4d ToMatrix()
        {
            var center = CenterViewModel.Value;
            var m1 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                -center.X, -center.Y, -center.Z, 1.0
                );

            var rx = AngleViewModel.X.Value / 180.0 * System.Math.PI;
            var ry = AngleViewModel.Y.Value / 180.0 * System.Math.PI;
            var rz = AngleViewModel.Z.Value / 180.0 * System.Math.PI;

            var rot = Matrix3d.RotationZ(rz) * Matrix3d.RotationY(ry) * Matrix3d.RotationX(rx);
            var m2 = new Matrix4d(rot);

            var m3 = new Matrix4d
                (
                1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                center.X, center.Y, center.Z, 1.0
                );

            return m1 * m2 * m3;
        }

    }
}
