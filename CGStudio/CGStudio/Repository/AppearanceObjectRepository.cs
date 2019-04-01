namespace PG.CGStudio
{
    public class AppearanceObjectRepository
    {
        private PG.CLI.AppearanceObjectRepositoryAdapter adapter;

        private LightObjectRepository light;

        public PG.CLI.AppearanceObjectRepositoryAdapter Adapter { get { return adapter; } }

        public AppearanceObjectRepository()
        {
            this.adapter = new PG.CLI.AppearanceObjectRepositoryAdapter();
            this.light = new LightObjectRepository();
        }
   }
}
