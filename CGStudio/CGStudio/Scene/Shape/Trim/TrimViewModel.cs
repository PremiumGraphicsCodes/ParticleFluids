using PG.CGStudio.Object.Select;
using PG.CGStudio.Selection;
using Prism.Mvvm;
using Reactive.Bindings;

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
            /*
            for(var region in regions)
            {
                region.IsInside()
            }
            */

        }
    }
}
