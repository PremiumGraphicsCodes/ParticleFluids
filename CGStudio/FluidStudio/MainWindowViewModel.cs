using FluidStudio.Physics;
using FluidStudio.Scene;
using PG.Control.OpenGL;
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

        public SceneListViewModel SceneListViewModel { get; }

        public PhysicsSceneListViewModel PhysicsSceneListViewModel { get; }


        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container)
        {
            this.regionManager = regionManager;

            var mainModel = container.Resolve<MainModel>();
            var world = container.Resolve<SceneList>();
            Canvas = container.Resolve<Canvas3d>();

            this.NavigateCommand.Subscribe(OnNavigate);

            this.FileIOViewModel = new FileIOViewModel(mainModel, world, Canvas);
            this.CameraControlViewModel = new CameraControlViewModel(world, Canvas);

            this.SceneListViewModel = new SceneListViewModel(regionManager, world);
            this.PhysicsSceneListViewModel = new PhysicsSceneListViewModel(regionManager, world);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

    }
}
