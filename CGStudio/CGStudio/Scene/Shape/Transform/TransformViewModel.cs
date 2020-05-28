using PG.CGStudio.Object.Select;
using PG.CGStudio.Scene.Shape.Transform;
using PG.CGStudio.Scene.Shape.Transform.Scale;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase, INavigationAware
    {
        public ShapeSelectViewModel SelectViewModel { get; }

        public TranslateViewModel TranslateViewModel { get; }

        public ScaleViewModel ScaleViewModel { get; }

        public RotateViewModel RotateViewModel { get; }
        
        public TransformViewModel(SceneListModel world, Canvas3d canvas)
        {
            this.SelectViewModel = new ShapeSelectViewModel(world, canvas);
            this.TranslateViewModel = new TranslateViewModel(world, canvas);
            this.ScaleViewModel = new ScaleViewModel(world, canvas);
            this.RotateViewModel = new RotateViewModel(world, canvas);
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {

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
