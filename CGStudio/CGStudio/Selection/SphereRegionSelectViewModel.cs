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
    public class SphereRegionSelectViewModel : BindableBase
    {
        public IEnumerable<Sphere3d> Spheres { get { return spheres; } }

        private List<Sphere3d> spheres = new List<Sphere3d>();

        public ReactiveProperty<double> Radius { get; }
            = new ReactiveProperty<double>(1.0);

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public SphereRegionSelectViewModel()
        {
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new PickUICtrl(10, SceneType.AllScene);
            picker.AddAction(OnPicked);
            HwndHostPresenter3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            var model = World.Instance.Adapter;
            var position = World.Instance.Scenes.GetPosition( id );

            var sphere = new Sphere3d(Radius.Value, position);
            var builder = new WireFrameBuilder();
            builder.Add(sphere, 24, 24);
            var appearance = new WireAppearance
            {
                Width = 1.0f,
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f)
            };

            World.Instance.Scenes.AddWireFrameScene(builder.ToWireFrame(), "Item",appearance, 0);

            HwndHostPresenter3d.Instance.Update(World.Instance);
            HwndHostPresenter3d.Instance.Render();

            spheres.Add(sphere);

            HwndHostPresenter3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
