using FluidStudio.FileIO;
using FluidStudio.Physics;
using FluidStudio.Physics.Solver;
using FluidStudio.Scene.VDB;
using FluidStudio.Tool.Modeling;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Ioc;
using Prism.Unity;
using System.Windows;

namespace FluidStudio
{
    public partial class App : PrismApplication
    {
        private Canvas3d canvas;
        private MainModel model;

        protected override Window CreateShell()
        {
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            this.model = new MainModel();
            containerRegistry.RegisterInstance<MainModel>(model);
            containerRegistry.RegisterInstance<SceneList>(model.Scenes);

            this.canvas = new Canvas3d(model.Scenes);
            containerRegistry.RegisterInstance<Canvas3d>(canvas);

            model.VDBModel.Init(model.Scenes);

            containerRegistry.RegisterForNavigation<Scene.ParticleSystem.BoxGenerationView>("PSBoxGeneration");
            containerRegistry.RegisterForNavigation<Scene.ParticleSystem.SphereGenerationView>("PSSphereGeneration");
            containerRegistry.RegisterForNavigation<Scene.ParticleSystem.QuadGenerationView>("PSQuadGeneration");

            containerRegistry.RegisterForNavigation<Scene.PolygonMesh.BoxGenerationView>("PMBoxGeneration");

            containerRegistry.RegisterForNavigation<Scene.CSG.BoxGenerationView>("CSGBoxGeneration");

            containerRegistry.RegisterForNavigation<MeshToVolumeView>("MeshToVolume");
            containerRegistry.RegisterForNavigation<VolumeToPSView>("VolumeToPS");

            containerRegistry.RegisterForNavigation<SolverSceneView>("SolverUpdate");
            containerRegistry.RegisterForNavigation<FluidSceneView>("FluidUpdate");
            containerRegistry.RegisterForNavigation<CSGBoundarySceneView>("CSGBoundaryUpdate");

            containerRegistry.RegisterForNavigation<ImportView>("Import");
            containerRegistry.RegisterForNavigation<ExportView>("Export");

            containerRegistry.RegisterForNavigation<VDBSceneView>("VDBScene");
        }
    }
}