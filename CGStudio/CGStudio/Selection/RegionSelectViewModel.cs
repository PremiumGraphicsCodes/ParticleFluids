using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Linq;

namespace PG.CGStudio.Selection
{
    public class RegionSelectViewModel
    {
        public SphereRegionSelectViewModel SphereRegionSelectViewModel { get; }

        public BoxRegionSelectViewModel BoxRegionSelectViewModel { get; }

        public CylinderRegionSelectViewModel CylinderRegionSelectViewModel { get; }

        public Space3d Space
        {
            get {
                var s = new Space3d();
                foreach(var r in Regions) {
                    s.Add(r);
                }
                return s;
            }
        }

        public IEnumerable<IVolume3d> Regions
        {
            get
            {
                var regions = new List<IVolume3d>();
                regions.Union( SphereRegionSelectViewModel.Spheres );
                regions.Union( BoxRegionSelectViewModel.Boxes );
                regions.Union( CylinderRegionSelectViewModel.Cylinders );
                return regions;
            }
        }

        public RegionSelectViewModel(SceneList world, Canvas3d canvas)
        {
            this.SphereRegionSelectViewModel = new SphereRegionSelectViewModel(world, canvas);
            this.BoxRegionSelectViewModel = new BoxRegionSelectViewModel(world, canvas);
            this.CylinderRegionSelectViewModel = new CylinderRegionSelectViewModel(world, canvas);
        }
    }
}
