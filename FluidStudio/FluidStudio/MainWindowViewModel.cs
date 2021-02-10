using FluidStudio.Physics;
using FluidStudio.Physics.MeshBoundary;
using FluidStudio.Scene;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Core.UI;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
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

        public ReactiveCommand FluidSceneCreateCommand { get; }
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
            this.FluidSceneCreateCommand.Subscribe(OnCreateFluidScene);
//            this.BoundarySceneCreateCommand.Subscribe(OnCreateBoundaryScene);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

        // create template.
        public void CreateDefaultTemplate()
        {
            mainModel.Scenes.CreateDefaultCameraScene();

            var scene = new SolverScene();
            scene.Create(mainModel.Scenes, new List<FluidScene>(), 2.0f, 0.03f, "Solver01");
            mainModel.PhysicsModel.Solvers.Add(scene);
        }

        private void OnCreateFluidScene()
        {
            var solver = mainModel.PhysicsModel.Solvers.FirstOrDefault();
            var fluidScene = new FluidScene();
            fluidScene.Create(mainModel.Scenes, mainModel.VDBModel, Canvas, 1.0f, 1.0f, 1.0f, "Fluid01", false);
            solver.Fluids.Add(fluidScene);
            Canvas.BuildShader(mainModel.Scenes, fluidScene.Id);
            Canvas.Render();
            mainModel.PhysicsModel.Solvers.Remove(solver);
            mainModel.PhysicsModel.Solvers.Add(solver);
        }
    }
}
