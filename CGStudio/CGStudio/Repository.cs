using PG.Core.Shape;

namespace PG.CGStudio
{
    public class Repository
    {
        private PG.CLI.RepositoryAdapter adapter;

        public PG.CLI.RepositoryAdapter Adapter { get { return adapter; } }


        public Repository()
        {
            this.adapter = new PG.CLI.RepositoryAdapter();
        }

        public void New()
        {
            this.adapter.Clear();
        }

        public bool Open(string filename)
        {
            return false;
        }

        public bool Save(string filename)
        {
            return false;
        }

        public bool Import(string filename)
        {
            return adapter.Import(filename);
        }

        public bool Export(string filename)
        {
            return adapter.Export(filename);
        }
    }
}
