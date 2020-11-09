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
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("CSGBoundary01");

        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand CreateCommand { get; }
            = new ReactiveCommand();

        public CSGBoundarySceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            CreateCommand.Subscribe(() => OnCreate(model, world, canvas));
            var min = new Vector3d(-100, -100, -100);
            var max = new Vector3d(100, 100, 100);
            BoxViewModel.Value = new Box3d(min, max);
        }

        private void OnCreate(MainModel model, SceneList world, Canvas3d canvas)
        {
            var physicsScene = model.PhysicsModel.Scenes.FirstOrDefault();
            var boundary = new CSGBoundaryScene(world, Name.Value, BoxViewModel.Value);
            physicsScene.CSGBoundaries.Add(boundary);
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as CSGBoundaryScene;
            if (item == null)
            {
                return;
            }
            Name.Value = item.Name;
            BoxViewModel.Value = item.Box;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }
    }
}
