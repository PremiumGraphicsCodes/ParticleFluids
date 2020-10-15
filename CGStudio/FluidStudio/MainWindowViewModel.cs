﻿using PG.Control.OpenGL;
using PG.Scene;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;
using Unity;

namespace FluidStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public Canvas3d Canvas { get; }

        public ReactiveCommand<string> NavigateCommand { get; }
            = new ReactiveCommand<string>();

        private IRegionManager regionManager;

        public FileIOViewModel FileIOViewModel { get; }

        public CameraControlViewModel CameraControlViewModel { get; }


        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container)
        {
            this.regionManager = regionManager;

            var world = container.Resolve<SceneList>();
            Canvas = container.Resolve<Canvas3d>();

            this.NavigateCommand.Subscribe(OnNavigate);

            this.FileIOViewModel = new FileIOViewModel(world, Canvas);
            this.CameraControlViewModel = new CameraControlViewModel(world, Canvas);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

    }
}