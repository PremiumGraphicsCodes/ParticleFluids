using FluidStudio.Physics;
using FluidStudio.Scene;
using PG.Control.OpenGL;
using PG.Core.Math;
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

        public TimeLineViewModel TimeLineViewModel { get; }

        public ReactiveCommand PhysicsSceneCreateCommand { get; }
            = new ReactiveCommand();

        private readonly MainModel mainModel;

        public MainWindowViewModel(IRegionManager regionManager, IUnityContainer container)
        {
            this.regionManager = regionManager;

            this.mainModel = container.Resolve<MainModel>();
            var world = container.Resolve<SceneList>();
            this.Canvas = container.Resolve<Canvas3d>();

            this.NavigateCommand.Subscribe(OnNavigate);

            this.FileIOViewModel = new FileIOViewModel(mainModel, world, Canvas);
            this.CameraControlViewModel = new CameraControlViewModel(world, Canvas);

            this.SceneListViewModel = new SceneListViewModel(regionManager, world);
            this.PhysicsSceneListViewModel = new PhysicsSceneListViewModel(regionManager, world, mainModel);
            this.TimeLineViewModel = new TimeLineViewModel(mainModel, world, Canvas);
            this.PhysicsSceneCreateCommand.Subscribe(OnCreatePhysicsScene);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

        private void OnCreatePhysicsScene()
        {
            var scene = new PhysicsScene();
            scene.CSGBoundaries.Add(new CSGBoundaryScene(mainModel.Scenes, "Boundary", new Box3d()));
            this.mainModel.PhysicsModel.Scenes.Add(scene);

        }

    }
}
