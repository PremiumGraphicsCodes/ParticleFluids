using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Selection
{
    public class BoxRegionSelectViewModel : BindableBase
    {
        public IEnumerable<Box3d> Boxes { get { return boxes; } }

        private List<Box3d> boxes = new List<Box3d>();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        private List<Vector3d> pickedPositions = new List<Vector3d>();

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public BoxRegionSelectViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new PickUICtrl(world, canvas, 10, SceneType.AllScene);
            picker.AddAction(OnPicked);
            canvas.UICtrl = picker;
        }

        private void OnPicked(SceneId id)
        {
            var position = world.GetPosition(id);
            pickedPositions.Add(position);

            if(pickedPositions.Count < 2)
            {
                return;
            }

            var box = new Box3d(pickedPositions);
            var builder = new WireFrameBuilder();
            builder.Add(box);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f),
                Width = 1.0f
            };

            world.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);

            canvas.Update();
            canvas.Render();

            boxes.Add(box);

            canvas.UICtrl = new CameraUICtrl(world, canvas);
        }
    }
}
