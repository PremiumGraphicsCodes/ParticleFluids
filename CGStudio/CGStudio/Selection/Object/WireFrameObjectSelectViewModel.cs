using Prism.Mvvm;
using Prism.Regions;

namespace PG.CGStudio.Selection.Object
{
    public class WireFrameObjectSelectViewModel : BindableBase, INavigationAware
    {
        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            ;
        }
    }
}
