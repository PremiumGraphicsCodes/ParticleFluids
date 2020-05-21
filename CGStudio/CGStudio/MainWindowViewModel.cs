using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Unity;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public DelegateCommand<string> NavigateCommand { get; }

        private IRegionManager regionManager;

        public FileIOViewModel FileIOViewModel { get; }

        public CameraControlViewModel CameraControlViewModel { get; }

        public UIControlViewModel UIControlViewModel { get; }

        private static MainWindowViewModel instance;

        public static MainWindowViewModel Instance
        {
            get
            {
                return instance;
            }
        }

        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container, World world)
        {
            instance = this;

            this.regionManager = regionManager;
            NavigateCommand = new DelegateCommand<string>(OnNavigate);// (name => );
            this.FileIOViewModel = new FileIOViewModel(world);
            this.CameraControlViewModel = new CameraControlViewModel(world);
            this.UIControlViewModel = new UIControlViewModel(world);
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
