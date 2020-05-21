﻿using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Control.OpenGL;
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

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand CancelCommand { get; }
            = new ReactiveCommand();

        private readonly World world;

        private readonly Canvas3d canvas;

        public RotateViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.OkCommand.Subscribe(OnOk);
            this.CancelCommand.Subscribe(OnCancel);

            this.ShapeSelectViewModel = new ShapeSelectViewModel(world);

            this.ShapeSelectViewModel.Picker.AddAction(OnSelected);
        }

        private void OnSelected(ObjectId id)
        {
            if (id.parentId == 0)
            {
                return;
            }

            var center = world.Scenes.GetCenter(id.parentId);
            CenterViewModel.Value = center;
            canvas.UICtrl = new RotateUICtrl(this, canvas);
        }


        private void OnOk()
        {
            world.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            OnCancel();

            world.Scenes.Clear(0);
            world.Scenes.ShowBoundingBox(ShapeSelectViewModel.Id.Value);
        }

        private void OnCancel()
        {
            world.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, Matrix4d.Identity());
            canvas.Update(world);
            canvas.Render();

            AngleViewModel.Value = new Vector3d(0, 0, 0);
        }

        public void SetMatrix(bool doRender)
        {
            world.Scenes.SetMatrix(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                canvas.Update(world);
                canvas.Render();
            }
        }

        public void Transform(bool doRender)
        {
            world.Scenes.Transform(ShapeSelectViewModel.Id.Value, ToMatrix());

            if (doRender)
            {
                canvas.Update(world);
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
