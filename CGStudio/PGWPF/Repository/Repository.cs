using PG.Core.Shape;

namespace PG.CGStudio
{
    public class Repository
    {
        private PG.CLI.RepositoryAdapter adapter;

        static Repository instance;

        public static Repository Instance { get { return instance; } }

        public PG.CLI.RepositoryAdapter Adapter { get { return adapter; } }

        public ObjectRepository Objects;

        public Repository()
        {
            adapter = new PG.CLI.RepositoryAdapter();
            instance = this;
            this.Objects = new ObjectRepository(adapter.Objects());
        }

        public void New()
        {
        }

        public bool Open(string filename)
        {
            return instance.Open(filename);
        }

        public bool Save(string filename)
        {
            return instance.Save(filename);
        }

        public void Import(string filename)
        {

        }

        public void Export(string filename)
        {

        }
    }
}
