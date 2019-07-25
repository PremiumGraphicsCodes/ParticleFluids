using System.Windows;
using PG.CGStudio.Light;
using PG.CGStudio.Material;
using PG.CGStudio.Object;
using PG.CGStudio.Scene.Appearance.Light;
using PG.CGStudio.Scene.Appearance.Material;
using PG.CGStudio.Selection;
using PG.CGStudio.Selection.Object;
using PG.CGStudio.Texture;
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
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.BoxGenerationView>("PCBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.SphereGenerationView>("PCSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.CylinderGenerationView>("PCCylinderGeneration");

            containerRegistry.RegisterForNavigation<Generation.WireFrame.BoxGenerationView>("WFBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.SphereGenerationView>("WFSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.CylinderGenerationView>("WFCylinderGeneration");

            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.BoxGenerationView>("PMBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.SphereGenerationView>("PMSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.CylinderGenerationView>("PMCylinderGeneration");

            containerRegistry.RegisterForNavigation<MaterialAddView>("MaterialAdd");
            containerRegistry.RegisterForNavigation<MaterialEditView>("MaterialEdit");

            containerRegistry.RegisterForNavigation<LightAddView>("LightAdd");
            containerRegistry.RegisterForNavigation<LightEditView>("LightEdit");
            containerRegistry.RegisterForNavigation<TextureEditView>("TextureEdit");
            containerRegistry.RegisterForNavigation<SceneView>("Object");

            containerRegistry.RegisterForNavigation<Object.Select.ObjectSelectView>("Select");
            containerRegistry.RegisterForNavigation<Object.Transform.TransformView>("Transform");

            containerRegistry.RegisterForNavigation<ParticleSystemObjectSelectView>("ParticleSystemSelect");
            containerRegistry.RegisterForNavigation<WireFrameObjectSelectView>("WireFrameSelect");
            containerRegistry.RegisterForNavigation<PolygonMeshObjectSelectView>("PolygonMeshSelect");

            containerRegistry.RegisterForNavigation<SphereRegionSelectView>("SphereRegionSelection");
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
