using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
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

        public BoxRegionSelectViewModel()
        {
            this.PickCommand.Subscribe(OnPickUI);
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
            var position = MainModel.Instance.World.GetPosition(id);
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

            MainModel.Instance.World.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);

            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();

            boxes.Add(box);

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
