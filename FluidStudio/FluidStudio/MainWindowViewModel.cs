using FluidStudio.Physics;
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

        public ReactiveCommand BoundarySceneCreateCommand { get; }
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
            this.BoundarySceneCreateCommand.Subscribe(OnCreateBoundaryScene);
        }

        private void OnNavigate(string name)
        {
            regionManager.RequestNavigate("ContentRegion", name);
        }

        // create template.
        public void CreateDefaultTemplate()
        {
            mainModel.Scenes.CreateDefaultCameraScene();

            var scene = new SolverScene(mainModel.Scenes);
            scene.Fluids = new List<FluidScene>();
            scene.CSGBoundaries = new List<CSGBoundaryScene>();
            scene.EffectLength = 0.5f;
            scene.TimeStep = 0.03f;
            scene.Name = "Solver01";
            scene.Send();
            mainModel.PhysicsModel.Solvers.Add(scene);
        }

        private void OnCreateFluidScene()
        {
            var solver = mainModel.PhysicsModel.Solvers.FirstOrDefault();
            var fluidScene = new FluidScene(mainModel.Scenes, solver, mainModel.VDBModel, Canvas);
            fluidScene.ParticleRadius = 0.5f;
            fluidScene.Density = 1000.0f;
            fluidScene.Stiffness = 1.0f;
            fluidScene.Viscosity = 1.0f;
            fluidScene.Name = "Fluid01";
            fluidScene.IsBoundary = false;
            fluidScene.Send();
            solver.Fluids.Add(fluidScene);
            solver.Send();
            Canvas.BuildShader(mainModel.Scenes, fluidScene.Id);
            Canvas.Render();
            mainModel.PhysicsModel.Solvers.Remove(solver);
            mainModel.PhysicsModel.Solvers.Add(solver);
        }

        private void OnCreateBoundaryScene()
        {
            var solver = mainModel.PhysicsModel.Solvers.FirstOrDefault();
            var box = new Box3d(new Vector3d(-100, 0, -100), new Vector3d(100, 100, 100));
            var boundaryScene = new CSGBoundaryScene(solver, mainModel.Scenes);
            boundaryScene.Name = "Boundary";
            boundaryScene.BoundingBox= box;
            boundaryScene.Send();
            solver.CSGBoundaries.Add(boundaryScene);
            solver.Send();
            Canvas.BuildShader(mainModel.Scenes, boundaryScene.Id);
            Canvas.Render();
            mainModel.PhysicsModel.Solvers.Remove(solver);
            mainModel.PhysicsModel.Solvers.Add(solver);
        }
    }
}
