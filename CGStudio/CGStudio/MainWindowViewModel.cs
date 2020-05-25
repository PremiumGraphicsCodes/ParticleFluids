using PG.Control.OpenGL;
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

        public Canvas3d Canvas { get; }

        private static MainWindowViewModel instance;

        public static MainWindowViewModel Instance
        {
            get
            {
                return instance;
            }
        }

        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container, World world, Canvas3d canvas)
        {
            instance = this;
            this.Canvas = canvas;

            this.regionManager = regionManager;
            NavigateCommand = new DelegateCommand<string>(OnNavigate);// (name => );
            this.FileIOViewModel = new FileIOViewModel(world, canvas);
            this.CameraControlViewModel = new CameraControlViewModel(world, canvas);
            this.UIControlViewModel = new UIControlViewModel(world, canvas);
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
