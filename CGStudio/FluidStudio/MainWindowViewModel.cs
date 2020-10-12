using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public Canvas3d Canvas { get; }

        private IRegionManager regionManager;

        public MainWindowViewModel()
        {
            var world = new SceneList();
            Canvas = new Canvas3d(world);
        }
    }
}
