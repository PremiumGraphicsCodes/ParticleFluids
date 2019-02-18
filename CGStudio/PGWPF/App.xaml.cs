using System.Windows;

namespace PG.CGStudio
{
    public partial class App : Application
    {
        private Repository model;

        protected override void OnStartup(StartupEventArgs e)
        {
            this.model = new Repository();
        }
    }
}
