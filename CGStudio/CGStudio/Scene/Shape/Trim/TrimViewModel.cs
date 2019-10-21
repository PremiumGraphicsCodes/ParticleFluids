using PG.CGStudio.Object.Select;
using PG.CGStudio.Selection;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.Trim
{
    public class TrimViewModel : BindableBase
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public SphereRegionSelectViewModel SphereRegionSelectViewModel { get; }
            = new SphereRegionSelectViewModel();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();
    }
}
