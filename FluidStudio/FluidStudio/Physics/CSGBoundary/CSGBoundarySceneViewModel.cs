using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Core.Math;
using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Linq;

namespace FluidStudio.Physics
{
    public class CSGBoundarySceneViewModel : INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("CSGBoundary01");

        public Box3dViewModel BoundingBoxViewModel { get; }

        private CSGBoundaryScene scene;

        private readonly MainModel model;

        private readonly Canvas3d canvas;

        public CSGBoundarySceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.model = model;
            this.canvas = canvas;
            var min = new Vector3d(-100, 0, -100);
            var max = new Vector3d(100, 100, 100);
            BoundingBoxViewModel = new Box3dViewModel();
            BoundingBoxViewModel.Value = new Box3d(min, max);
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
            this.BoundingBoxViewModel.Value = item.BoundingBox;
            //this.BoxViewModel.Value = item.Box;
            this.scene = item;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        private void OnSolidChanged(int id)
        {
            if(scene == null)
            {
                return;
            }
            this.scene.Update(model.Scenes, Name.Value, this.BoundingBoxViewModel.Value);
        }
   }
}
