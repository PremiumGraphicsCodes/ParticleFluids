using FluidStudio.Physics;
using FluidStudio.Scene;
using PG.Control.OpenGL;
using PG.Core.Math;
using PG.Core.UI;
using PG.Scene;
using Prism.Commands;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Windows.Documents;
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

        // create template.
        public void CreateDefaultTemplate()
        {
            OnCreateParticles();
            OnCreatePhysicsScene();
        }

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
            var newId = world.AddParticleSystemScene(positions, "PSBox", appearance, 1);
            this.Canvas.Camera.Fit();
            this.Canvas.BuildShader(world, newId);
            this.Canvas.Render();
        }

        private void OnCreatePhysicsScene()
        {
            var min = new Vector3d(0.0, 0.0, 0.0);
            var max = new Vector3d(10.0, 10.0, 10.0);
            var dx = 1.0;
            var dy = 1.0;
            var dz = 1.0;
            var positions = new List<Vector3d>();
            for (var x = min.X; x < max.X; x += dx)
            {
                for (var y = min.Y; y < max.Y; y += dy)
                {
                    for (var z = min.Z; z < max.Z; z += dz)
                    {
                        var p = new Vector3d(x, y, z);
                        positions.Add(p);
                    }
                }
            }
            var particleSystemSceneId = mainModel.Scenes.AddParticleSystemScene(positions, "Particles01", new PG.Core.UI.ParticleAppearance(), 1);

            Canvas.BuildShader(mainModel.Scenes, particleSystemSceneId);

            var fluids = new List<FluidScene>();
            var fluidScene = new FluidScene(mainModel.Scenes, particleSystemSceneId, 1.0f, 1.0f, "Fluid01");
            fluids.Add( fluidScene );
            var box = new Box3d( new Vector3d(-100, -100, -100), new Vector3d(100, 100, 100));
            var boundaries = new List<CSGBoundaryScene>();
            boundaries.Add(new CSGBoundaryScene(mainModel.Scenes, "Boundary", box));
            var scene = new SolverScene();
            scene.Create(mainModel.Scenes, fluids, boundaries, 0.03f, "Solver01");
            this.mainModel.PhysicsModel.Scenes.Add(scene);

            Canvas.BuildShader(mainModel.Scenes, fluidScene.Id);
            Canvas.Render();
        }
    }
}
