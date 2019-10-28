using Reactive.Bindings;

namespace PG.CGStudio.Selection
{
    public class RegionSelectViewModel
    {
        public SphereRegionSelectViewModel SphereRegionSelectViewModel { get; }
            = new SphereRegionSelectViewModel();

        public BoxRegionSelectViewModel BoxRegionSelectViewModel { get; }
            = new BoxRegionSelectViewModel();

        public CylinderRegionSelectViewModel CylinderRegionSelectViewModel { get; }
            = new CylinderRegionSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public RegionSelectViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            
        }
    }
}
