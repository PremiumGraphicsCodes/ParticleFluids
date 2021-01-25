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

        public ReactiveCommand PhysicsSceneCreateCommand { get; }
            = new ReactiveCommand();

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
            this.PhysicsSceneCreateCommand.Subscribe(OnCreatePhysicsScene);
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
            //OnCreateSolid();
            OnCreateParticles();
            //OnCreateVDBVolume();
            //OnCreateVDBPoints();
            OnCreatePhysicsScene();
        }

        private int sourcePSId;
        private int boundaryPSId;

        private void OnCreateParticles()
        {
            var world = mainModel.Scenes;
            var positions = new List<Vector3d>();
            var min = new Vector3d(0.0, 0.0, 0.0);
            var max = new Vector3d(10.0, 10.0, 10.0);
            var box = new Box3d(min, max);
            sourcePSId = CreateBoxParticles(box, "SourcePS");
            boundaryPSId = CreateBoxParticles(new Box3d( new Vector3d(-10, -2, -10), new Vector3d(10, 0, 10)), "BoundaryPS");
        }

        private int CreateBoxParticles(Box3d box, string name)
        {
            var world = mainModel.Scenes;
            var positions = new List<Vector3d>();

            var length = box.Length;
            var min = box.Min;
            var max = box.Max;
            for (var x = min.X; x < max.X; x += 1.0)
            {
                for (var y = min.Y; y < max.Y; y += 1.0)
                {
                    for (var z = min.Z; z < max.Z; z += 1.0)
                    {
                        var p = new Vector3d(x, y, z);
                        positions.Add(p);
                    }
                }
            }
            int id = mainModel.VDBModel.CreateVDBPoints(mainModel.Scenes, positions, name);
            this.Canvas.Camera.Fit();
            this.Canvas.BuildShader(world, id);
            this.Canvas.Render();
            return id;
        }

        private int volumeId;

        private void OnCreatePhysicsScene()
        {
            Canvas.BuildShader(mainModel.Scenes, sourcePSId);

            var fluids = new List<FluidScene>();
            var fluidScene1 = new FluidScene();
            fluidScene1.Create(mainModel.Scenes, sourcePSId, 1.0f, 1.0f, 1.0f, "Fluid01", false);
            fluidScene1.CreateVolume(mainModel.Scenes, mainModel.VDBModel, Canvas);
            fluids.Add( fluidScene1 );

            var fluidScene2 = new FluidScene();
            fluidScene2.Create(mainModel.Scenes, boundaryPSId, 5.0f, 1.0f, 1.0f, "Boundary01", true);
            fluidScene2.CreateVolume(mainModel.Scenes, mainModel.VDBModel, Canvas);
            fluids.Add(fluidScene2);

            var boundaries = new List<CSGBoundaryScene>();
            //boundaries.Add(new CSGBoundaryScene(mainModel.Scenes, "Boundary", solidId));
            var scene = new SolverScene();
            scene.Create(mainModel.Scenes, fluids, boundaries, 0.03f, "Solver01");
            this.mainModel.PhysicsModel.Solvers.Add(scene);

            Canvas.BuildShader(mainModel.Scenes, fluidScene1.Id);
            Canvas.BuildShader(mainModel.Scenes, fluidScene2.Id);
            Canvas.Render();
        }

        private void OnCreateFluidScene()
        {
            var solver = mainModel.PhysicsModel.Solvers.FirstOrDefault();
            var fluidScene = new FluidScene();
            fluidScene.Create(mainModel.Scenes, sourcePSId, 1.0f, 1.0f, 1.0f, "Fluid01", false);
            fluidScene.CreateVolume(mainModel.Scenes, mainModel.VDBModel, Canvas);
            solver.Fluids.Add(fluidScene);
            Canvas.BuildShader(mainModel.Scenes, fluidScene.Id);
            Canvas.Render();
            mainModel.PhysicsModel.Solvers.Remove(solver);
            mainModel.PhysicsModel.Solvers.Add(solver);
        }

        private void OnCreateVDBVolume()
        {
            this.volumeId = mainModel.VDBModel.CreateVDBVolume(mainModel.Scenes, "VDBVolume", true);
            Canvas.BuildShader(mainModel.Scenes, volumeId);
            Canvas.Render();
        }

        private void OnCreateVDBPoints()
        {
            var id = mainModel.VDBModel.CreateVDBPoints(mainModel.Scenes, new List<Vector3d>(), "VDBPoints");
            Canvas.BuildShader(mainModel.Scenes, id);
            Canvas.Render();
        }
    }
}
