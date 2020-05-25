using System.Windows;
using PG.CGStudio.Light;
using PG.CGStudio.Material;
using PG.CGStudio.Object;
using PG.CGStudio.Scene;
using PG.CGStudio.Scene.Appearance.Light;
using PG.CGStudio.Scene.Appearance.Material;
using PG.CGStudio.Scene.Appearance.Texture;
using PG.CGStudio.Scene.Shape.ParticleSystem;
using PG.CGStudio.Scene.Shape.PolygonMesh;
using PG.CGStudio.Scene.Shape.PolygonMesh.Generation;
using PG.CGStudio.Scene.Shape.Trim;
using PG.CGStudio.Scene.Shape.WireFrame;
using PG.CGStudio.Scene.Shape.WireFrame.Generation;
using PG.CGStudio.Selection;
using PG.CGStudio.Texture;
using PG.Control.OpenGL;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Unity;

namespace PG.CGStudio
{
    public partial class App : PrismApplication
    {
        private World world;
        private Canvas3d canvas;

        protected override Window CreateShell()
        {
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            this.world = new World();
            containerRegistry.RegisterInstance<World>(world);
            this.canvas = new Canvas3d(world);
            containerRegistry.RegisterInstance<Canvas3d>(canvas);

            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.BoxGenerationView>("PSBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.SphereGenerationView>("PSSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.ParticleSystem.CylinderGenerationView>("PSCylinderGeneration");
            containerRegistry.RegisterForNavigation<Scene.Shape.ParticleSystem.Generation.CircleGenerationView>("PSCircleGeneration");
            containerRegistry.RegisterForNavigation<Scene.Shape.ParticleSystem.Generation.ConeGenerationView>("PSConeGeneration");

            containerRegistry.RegisterForNavigation<Generation.WireFrame.BoxGenerationView>("WFBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.SphereGenerationView>("WFSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.CylinderGenerationView>("WFCylinderGeneration");
            containerRegistry.RegisterForNavigation<Generation.WireFrame.EllipseGenerationView>("WFCircleGeneration");
            containerRegistry.RegisterForNavigation<Scene.Shape.WireFrame.Generation.ConeGenerationView>("WFConeGeneration");

            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.BoxGenerationView>("PMBoxGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.SphereGenerationView>("PMSphereGeneration");
            containerRegistry.RegisterForNavigation<Generation.PolygonMesh.CylinderGenerationView>("PMCylinderGeneration");
            containerRegistry.RegisterForNavigation<CircleGenerationView>("PMCircleGeneration");
            containerRegistry.RegisterForNavigation<Scene.Shape.PolygonMesh.Generation.ConeGenerationView>("PMConeGeneration");

            containerRegistry.RegisterForNavigation<ParticleSystemEditView>("ParticleSystemEdit");
            containerRegistry.RegisterForNavigation<WireFrameEditView>("WireFrameEdit");
            containerRegistry.RegisterForNavigation<PolygonMeshEditView>("PolygonMeshEdit");
            containerRegistry.RegisterForNavigation<FaceGroupEditView>("FaceGroupEdit");

            containerRegistry.RegisterForNavigation<MaterialAddView>("MaterialAdd");
            containerRegistry.RegisterForNavigation<MaterialEditView>("MaterialEdit");

            containerRegistry.RegisterForNavigation<LightAddView>("LightAdd");
            containerRegistry.RegisterForNavigation<LightEditView>("LightEdit");

            containerRegistry.RegisterForNavigation<TextureAddView>("TextureAdd");
            containerRegistry.RegisterForNavigation<TextureEditView>("TextureEdit");

            containerRegistry.RegisterForNavigation<SceneView>("Object");

            containerRegistry.RegisterForNavigation<Object.Select.ShapeSelectView>("Select");
            containerRegistry.RegisterForNavigation<Object.Transform.TransformView>("Transform");

            containerRegistry.RegisterForNavigation<SphereRegionSelectView>("SphereRegionSelection");
            containerRegistry.RegisterForNavigation<CylinderRegionSelectView>("CylinderRegionSelection");
            containerRegistry.RegisterForNavigation<BoxRegionSelectView>("BoxRegionSelection");
            containerRegistry.RegisterForNavigation<RegionSelectView>("RegionSelection");

            containerRegistry.RegisterForNavigation<TrimView>("Trim");
            containerRegistry.RegisterForNavigation<SceneExportView>("SceneExport");
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
