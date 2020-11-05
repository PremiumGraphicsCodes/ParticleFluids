using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Linq;

namespace FluidStudio.Physics
{
    public class CSGBoundarySceneViewModel
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
        }

        private void OnCreate(MainModel model, SceneList world, Canvas3d canvas)
        {
            var physicsScene = model.PhysicsModel.Scenes.FirstOrDefault();
            var boundary = new CSGBoundaryScene(world, Name.Value, BoxViewModel.Value);
            physicsScene.CSGBoundaries.Add(boundary);
        }
    }
}
