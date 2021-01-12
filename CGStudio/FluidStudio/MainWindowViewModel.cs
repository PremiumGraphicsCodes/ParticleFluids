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
            OnCreateSolid();
            OnCreateParticles();
            OnCreateMesh();
            OnCreatePhysicsScene();
        }

        private int particleSystemId;

        private void OnCreateParticles()
        {
            var world = mainModel.Scenes;
            var positions = new List<Vector3d>();
            var min = new Vector3d(0.0, 0.0, 0.0);
            var max = new Vector3d(10.0, 10.0, 10.0);
            var box = new Box3d(min, max);
            var length = box.Length;
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
            var appearance = new ParticleAppearance();
            appearance.Color = new PG.Core.Graphics.ColorRGBA(1, 1, 1, 1);
            appearance.Size = 10.0f;
            this.particleSystemId = world.AddParticleSystemScene(positions, "PSBox", appearance, 1);
            this.Canvas.Camera.Fit();
            this.Canvas.BuildShader(world, particleSystemId);
            this.Canvas.Render();
        }

        private int meshId;

        private void OnCreateMesh()
        {
            /*
            var world = mainModel.Scenes;
            var builder = new PolygonMeshBuilder();
            builder.Add(new Box3d(new Vector3d(0,0,0), new Vector3d(10,10,10)));
            this.meshId = world.AddPolygonMeshScene(builder.ToPolygonMesh(), "Mesh", 1);
            */
            var world = mainModel.Scenes;
            this.meshId = mainModel.VDBModel.CreateVDBMesh(world);
            this.Canvas.Camera.Fit();
            this.Canvas.BuildShader(world, meshId);
            this.Canvas.Render();
        }

        private int solidId;

        private void OnCreateSolid()
        {
            var world = mainModel.Scenes;
            var box = new Box3d(new Vector3d(-10, 0, -100), new Vector3d(100, 100, 100));
            var color = new PG.Core.Graphics.ColorRGBA(1, 1, 1, 1);
            var newId = world.AddSolidScene(box, "CSGBox", color, 1);
            this.solidId = newId;
            this.Canvas.Camera.Fit();
            this.Canvas.BuildShader(world, newId);
            this.Canvas.Render();
        }

        private void OnCreatePhysicsScene()
        {
            Canvas.BuildShader(mainModel.Scenes, particleSystemId);

            var fluids = new List<FluidScene>();
            var fluidScene = new FluidScene();
            fluidScene.Create(mainModel.Scenes, particleSystemId, 1.0f, 1.0f, "Fluid01", false);
            fluidScene.PolygonMeshId = this.meshId;
            fluids.Add( fluidScene );
            var boundaries = new List<CSGBoundaryScene>();
            boundaries.Add(new CSGBoundaryScene(mainModel.Scenes, "Boundary", solidId));
            var scene = new SolverScene();
            scene.Create(mainModel.Scenes, fluids, boundaries, 0.03f, "Solver01");
            this.mainModel.PhysicsModel.Solvers.Add(scene);

            Canvas.BuildShader(mainModel.Scenes, fluidScene.Id);
            Canvas.Render();
        }

        private void OnCreateFluidScene()
        {
            var solver = mainModel.PhysicsModel.Solvers.FirstOrDefault();
            var fluidScene = new FluidScene();
            fluidScene.Create(mainModel.Scenes, particleSystemId, 1.0f, 1.0f, "Fluid01", false);
            fluidScene.PolygonMeshId = this.meshId;
            solver.Fluids.Add(fluidScene);
            Canvas.BuildShader(mainModel.Scenes, fluidScene.Id);
            Canvas.Render();
            mainModel.PhysicsModel.Solvers.Remove(solver);
            mainModel.PhysicsModel.Solvers.Add(solver);
        }

        private void OnCreateBoundaryScene()
        {
            var solver = mainModel.PhysicsModel.Solvers.FirstOrDefault();
            solver.CSGBoundaries.Add(new CSGBoundaryScene(mainModel.Scenes, "Boundary", solidId));
            mainModel.PhysicsModel.Solvers.Remove(solver);
            mainModel.PhysicsModel.Solvers.Add(solver);
        }
    }
}
