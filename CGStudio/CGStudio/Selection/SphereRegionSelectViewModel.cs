using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Control.OpenGL;
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

        private readonly World world;

        public SphereRegionSelectViewModel(World world)
        {
            this.world = world;
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new PickUICtrl(world, 10, SceneType.AllScene);
            picker.AddAction(OnPicked);
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            var position = world.Scenes.GetPosition( id );

            var sphere = new Sphere3d(Radius.Value, position);
            var builder = new WireFrameBuilder();
            builder.Add(sphere, 24, 24);
            var appearance = new WireAppearance
            {
                Width = 1.0f,
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f)
            };

            world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "Item",appearance, 0);

            Canvas3d.Instance.Update(world);
            Canvas3d.Instance.Render();

            spheres.Add(sphere);

            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }
    }
}
