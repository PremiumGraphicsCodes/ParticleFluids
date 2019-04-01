using System.Windows;
using PG.CGStudio.Material;
using PG.Control.Graphics;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Unity;

namespace PG.CGStudio
{
    public partial class App : PrismApplication
    {
        private MainModel model;

        protected override Window CreateShell()
        {
            this.model = new MainModel();
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.ParticleSystemGenerationView>("PCGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.WireFrameGenerationView>("WFGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.PolygonMeshGenerationView>("PMGeneration");

            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.BoxGenerationView>("PCBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.SphereGenerationView>("PCSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.CylinderGenerationView>("PCCylinderGeneration");

            containerRegistry.RegisterForNavigation<Generation.WireFrame.BoxGenerationView>("WFBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.SphereGenerationView>("WFSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.CylinderGenerationView>("WFCylinderGeneration");

            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.BoxGenerationView>("PMBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.SphereGenerationView>("PMSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.SphereGenerationView>("PMCylinderGeneration");

            containerRegistry.RegisterForNavigation<MaterialEditView>("Material");
            containerRegistry.RegisterForNavigation<PointLightView>("Light");
            containerRegistry.RegisterForNavigation<TextureView>("Texture");
        }

        protected override void ConfigureModuleCatalog(IModuleCatalog moduleCatalog)
        {
            //moduleCatalog.AddModule<ModuleA.ModuleAModule>();
        }

        /*
        protected override void OnStartup(StartupEventArgs e)
        {
        }
        */
    }
}
