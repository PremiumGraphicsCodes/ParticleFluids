using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public DelegateCommand<string> NavigateCommand { get; }

        private IRegionManager regionManager;

        private static MainWindowViewModel instance;

        public static MainWindowViewModel Instance
        {
            get
            {
                return instance;
            }
        }

        public MainWindowViewModel(IRegionManager regionManager)
        {
            instance = this;

            this.regionManager = regionManager;
            NavigateCommand = new DelegateCommand<string>(OnNavigate);// (name => );
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

        public void NavigateWithParam(string name, NavigationParameters navigationParameters)
        {
            regionManager.RequestNavigate("ContentRegion", name, navigationParameters);
        }
    }
}
