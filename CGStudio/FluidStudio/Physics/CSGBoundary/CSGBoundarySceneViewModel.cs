using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System.Linq;

namespace FluidStudio.Physics
{
    public class CSGBoundarySceneViewModel : INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("CSGBoundary01");

        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        private CSGBoundaryScene scene;

        public CSGBoundarySceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            var min = new Vector3d(-100, -100, -100);
            var max = new Vector3d(100, 100, 100);
            BoxViewModel.Value = new Box3d(min, max);
            UpdateCommand.Subscribe(() => OnUpdate(model, world, canvas));
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as CSGBoundaryScene;
            if (item == null)
            {
                return;
            }
            this.Id.Value = item.Id;
            this.Name.Value = item.Name;
            this.BoxViewModel.Value = item.Box;
            this.scene = item;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        private void OnUpdate(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.scene.Update(world, Name.Value, BoxViewModel.Value);
        }
    }
}
