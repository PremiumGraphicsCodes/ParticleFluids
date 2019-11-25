using PG.CGStudio.Object.Select;
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
    public class CylinderRegionSelectViewModel : BindableBase
    {
        public IEnumerable<Cylinder3d> Cylinders { get { return cylinders; } }

        private readonly List<Cylinder3d> cylinders = new List<Cylinder3d>();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public CylinderRegionSelectViewModel()
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
            var position = MainModel.Instance.World.GetPosition(id);

            var cylinder = new Cylinder3d();
            var builder = new WireFrameBuilder();
            builder.Add(cylinder, 24, 24);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f),
                Width = 1.0f
            };

            MainModel.Instance.World.Items.AddWireFrameScene(builder.Build(), "", appearance);

            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();

            cylinders.Add( cylinder );

            Canvas3d.Instance.UICtrl = new CameraAndPickUICtrl();
        }
    }
}
