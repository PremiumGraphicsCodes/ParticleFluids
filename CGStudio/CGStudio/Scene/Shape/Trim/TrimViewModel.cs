using PG.CGStudio.Object.Select;
using PG.CGStudio.Selection;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Collections.Generic;
using Label = PG.TrimLabels;

namespace PG.CGStudio.Scene.Shape.Trim
{
    public class TrimViewModel : BindableBase
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }

        public SphereRegionSelectViewModel RegionSelectViewModel { get; }

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public TrimViewModel(SceneList world, Canvas3d canvas)
        {
            this.ShapeSelectViewModel = new ShapeSelectViewModel(world, canvas);
            this.RegionSelectViewModel = new SphereRegionSelectViewModel(world, canvas);
            this.world = world;
            this.canvas = canvas;
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var regions = RegionSelectViewModel.Spheres;
            var command = new PG.CLI.Command(Label.TrimCommandLabel);
            command.SetArg(Label.ShapeIdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg("Spheres", regions);
            command.Execute(world.Adapter);
            var newId = command.GetResult<int>(Label.NewIdLabel);

            //World.Instance.Items.Clear();

            canvas.Update();
            canvas.Render();

            world.Sync();
        }
    }
}
