using PG.CGStudio.Object.Select;
using PG.CGStudio.Selection;
using PG.Control.OpenGL;
using PG.Core.Math;
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

        private readonly World world;

        public TrimViewModel(World world)
        {
            this.ShapeSelectViewModel = new ShapeSelectViewModel(world);
            this.RegionSelectViewModel = new SphereRegionSelectViewModel(world);
            this.world = world;
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

            Canvas3d.Instance.Update(world);
            Canvas3d.Instance.Render();

            world.Scenes.Sync();
        }
    }
}
