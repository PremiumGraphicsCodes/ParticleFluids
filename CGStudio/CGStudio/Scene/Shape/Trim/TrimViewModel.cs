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

        public RegionSelectViewModel RegionSelectViewModel { get; }
            = new RegionSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public TrimViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var regions = RegionSelectViewModel.Regions;
            var command = new PG.CLI.Command(Label.TrimCommandLabel);
            command.SetArg<int>(Label.ShapeIdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg<IEnumerable<IVolume3d>>(Label.SpaceLabel, regions);
            command.Execute(MainModel.Instance.World.Adapter);
            var newId = command.GetResult<int>(Label.NewIdLabel);

        }
    }
}
