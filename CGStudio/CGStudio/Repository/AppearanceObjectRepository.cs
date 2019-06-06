namespace PG.CGStudio
{
    public class AppearanceObjectRepository
    {
        private PG.CLI.AppearanceObjectRepositoryAdapter adapter;

        public PG.CLI.AppearanceObjectRepositoryAdapter Adapter { get { return adapter; } }

        public AppearanceObjectRepository(PG.CLI.AppearanceObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
        }
   }
}
