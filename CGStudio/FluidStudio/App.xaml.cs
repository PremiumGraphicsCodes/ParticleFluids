using FluidStudio.Physics;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Ioc;
using Prism.Unity;
using System.Windows;

namespace FluidStudio
{
    public partial class App : PrismApplication
    {
        private SceneList world;
        private Canvas3d canvas;

        protected override Window CreateShell()
        {
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            this.world = new SceneList();
            containerRegistry.RegisterInstance<SceneList>(world);
            this.canvas = new Canvas3d(world);
            containerRegistry.RegisterInstance<Canvas3d>(canvas);

            containerRegistry.RegisterForNavigation<Scene.ParticleSystem.BoxGenerationView>("PSBoxGeneration");
            containerRegistry.RegisterForNavigation<Scene.ParticleSystem.SphereGenerationView>("PSSphereGeneration");
            containerRegistry.RegisterForNavigation<Scene.ParticleSystem.QuadGenerationView>("PSQuadGeneration");

            containerRegistry.RegisterForNavigation<FluidView>("FluidGeneration");
        }
    }
}