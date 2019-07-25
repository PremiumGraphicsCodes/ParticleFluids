using Prism.Mvvm;
using Prism.Regions;

namespace PG.CGStudio.Scene.Appearance.Texture
{
    public class TextureAddViewModel : BindableBase, INavigationAware
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
