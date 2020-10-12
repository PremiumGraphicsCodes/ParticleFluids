﻿using PG.Control.OpenGL;
using PG.Scene;
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

        private IRegionManager regionManager;

        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container)
        {
            this.regionManager = regionManager;

            var world = container.Resolve<SceneList>();
            Canvas = container.Resolve<Canvas3d>();
        }
    }
}
