using PG.Core.Math;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Linq;

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

        public IEnumerable<IVolume3d> Regions
        {
            get
            {
                var regions = new List<IVolume3d>();
                regions.Union( SphereRegionSelectViewModel.Spheres );
                regions.Add( BoxRegionSelectViewModel.BoxViewModel.Value );
                regions.Add( CylinderRegionSelectViewModel.CylinderViewModel.Value );
                return regions;
            }
        }

        public RegionSelectViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            
        }
    }
}
