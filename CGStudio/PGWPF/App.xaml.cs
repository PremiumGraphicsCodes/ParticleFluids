using System.Windows;
using PG.CGStudio.Generation.ParticleSystem;
using Prism.Ioc;
using Prism.Modularity;
using Prism.Unity;

namespace PG.CGStudio
{
    public partial class App : PrismApplication
    {
        private Repository model;

        protected override Window CreateShell()
        {
            this.model = new Repository();
            return Container.Resolve<MainWindow>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterForNavigation<BoxGenerationView>("PCBoxGeneration");
            containerRegistry.RegisterForNavigation<SphereGenerationView>("PCSphereGeneration");
            containerRegistry.RegisterForNavigation<CylinderGenerationView>("PCCylinderGeneration");
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
