using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public DelegateCommand<string> PCGenerationNavigateCommand { get; }

        public DelegateCommand<string> WFGenerationNavigateCommand { get; }

        public DelegateCommand<string> PMGenerationNavigateCommand { get; }

        public DelegateCommand<string> NavigateCommand { get; }

        private IRegionManager regionManager;

        public MainWindowViewModel(IRegionManager regionManager)
        {
            this.regionManager = regionManager;
            PCGenerationNavigateCommand = new DelegateCommand<string>(OnPCGenerationNavigate);
            WFGenerationNavigateCommand = new DelegateCommand<string>(OnWFGenerationNavigate);
            PMGenerationNavigateCommand = new DelegateCommand<string>(OnPMGenerationNaviate);

            NavigateCommand = new DelegateCommand<string>(OnNavigate);// (name => );
        }

        private void OnPCGenerationNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", "PCGeneration");
            regionManager.RequestNavigate("PCGenerationRegion", name);
        }

        private void OnWFGenerationNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", "WFGeneration");
            regionManager.RequestNavigate("WFGenerationRegion", name);
        }

        private void OnPMGenerationNaviate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", "PMGeneration");
            regionManager.RequestNavigate("PMGenerationRegion", name);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }
    }
}
