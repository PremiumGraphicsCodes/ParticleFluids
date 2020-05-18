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
            = new ShapeSelectViewModel();

        public SphereRegionSelectViewModel RegionSelectViewModel { get; }
            = new SphereRegionSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public TrimViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var regions = RegionSelectViewModel.Spheres;
            var command = new PG.CLI.Command(Label.TrimCommandLabel);
            command.SetArg(Label.ShapeIdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg("Spheres", regions);
            command.Execute(World.Instance.Adapter);
            var newId = command.GetResult<int>(Label.NewIdLabel);

            //World.Instance.Items.Clear();

            Canvas3d.Instance.Update(World.Instance);
            Canvas3d.Instance.Render();

            World.Instance.Scenes.Sync();
        }
    }
}
