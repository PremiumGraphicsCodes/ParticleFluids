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
            = new ShapeSelectViewModel();

        public TranslateViewModel TranslateViewModel { get; }
            = new TranslateViewModel();

        public ScaleViewModel ScaleViewModel { get; }
            = new ScaleViewModel();

        public RotateViewModel RotateViewModel { get; }
            = new RotateViewModel();

        public TransformViewModel()
        {
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
