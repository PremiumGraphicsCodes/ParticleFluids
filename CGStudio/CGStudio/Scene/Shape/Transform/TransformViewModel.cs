using PG.CGStudio.Object.Select;
using PG.CGStudio.Scene.Shape.Transform;
using PG.CGStudio.Scene.Shape.Transform.Scale;
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
        
        public TransformViewModel(World world)
        {
            this.SelectViewModel = new ShapeSelectViewModel(world);
            this.TranslateViewModel = new TranslateViewModel(world);
            this.ScaleViewModel = new ScaleViewModel(world);
            this.RotateViewModel = new RotateViewModel(world);
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
