using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics
{
    public class PhysicsSceneListViewModel
    {
        public ReadOnlyReactiveCollection<PhysicsSceneListViewModel> Items { get; }

        public PhysicsSceneListViewModel(IRegionManager regionManager, SceneList world)
        {
            /*
            this.world = world;
            this.regionManager = regionManager;
            Items = world.Scenes.ToReadOnlyReactiveCollection();
            */
        }

    }

}
