using PG.CGStudio.Object.Select;
using PG.CGStudio.Selection;
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
            command.Execute(MainModel.Instance.World.Adapter);
            var newId = command.GetResult<int>(Label.NewIdLabel);

            MainModel.Instance.World.Items.Clear();

            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();

            MainModel.Instance.World.Scenes.Sync();
        }
    }
}
