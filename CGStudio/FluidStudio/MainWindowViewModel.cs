using PG.Control.OpenGL;
using PG.Scene;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Unity;

namespace FluidStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public Canvas3d Canvas { get; }

        public DelegateCommand<string> NavigateCommand { get; }

        private IRegionManager regionManager;


        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container)
        {
            this.regionManager = regionManager;

            var world = container.Resolve<SceneList>();
            Canvas = container.Resolve<Canvas3d>();

            this.NavigateCommand = new DelegateCommand<string>(OnNavigate);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

    }
}
