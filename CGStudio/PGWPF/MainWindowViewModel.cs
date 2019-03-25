using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public DelegateCommand<string> PCGenerationNavigateCommand { get; }

        public DelegateCommand<string> NavigateCommand { get; }

        private IRegionManager regionManager;

        public MainWindowViewModel(IRegionManager regionManager)
        {
            this.regionManager = regionManager;
            PCGenerationNavigateCommand = new DelegateCommand<string>(OnPCGenerationNavigate);
            NavigateCommand = new DelegateCommand<string>(OnNavigate);// (name => );
        }

        private void OnPCGenerationNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", "PCGeneration");
            regionManager.RequestNavigate("PCGenerationRegion", name);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }
    }
}
