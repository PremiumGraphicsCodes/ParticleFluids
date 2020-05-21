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
    public class CylinderRegionSelectViewModel : BindableBase
    {
        public IEnumerable<Cylinder3d> Cylinders { get { return cylinders; } }

        private readonly List<Cylinder3d> cylinders = new List<Cylinder3d>();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        private readonly World world;

        private readonly Canvas3d canvas;

        public CylinderRegionSelectViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new PickUICtrl(world, 10, SceneType.AllScene);
            picker.AddAction(OnPicked);
            canvas.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            var position = world.Scenes.GetPosition(id);

            var cylinder = new Cylinder3d();
            var builder = new WireFrameBuilder();
            builder.Add(cylinder, 24, 24);
            var appearance = new WireAppearance
            {
                Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f),
                Width = 1.0f
            };

            world.Scenes.AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);

            canvas.Update(world);
            canvas.Render();

            cylinders.Add( cylinder );

            canvas.UICtrl = new CameraUICtrl(canvas);
        }
    }
}
