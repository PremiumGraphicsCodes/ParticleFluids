namespace PG.CGStudio
{
    public class AppearanceObjectRepository
    {
        private PG.CLI.AppearanceObjectRepositoryAdapter adapter;

        public PG.CLI.AppearanceObjectRepositoryAdapter Adapter { get { return adapter; } }

        public AppearanceObjectRepository()
        {
            this.adapter = new PG.CLI.AppearanceObjectRepositoryAdapter();
        }
   }
}
