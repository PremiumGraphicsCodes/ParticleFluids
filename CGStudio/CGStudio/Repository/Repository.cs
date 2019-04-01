using PG.Core.Shape;

namespace PG.CGStudio
{
    public class Repository
    {
        private PG.CLI.RepositoryAdapter adapter;

        public PG.CLI.RepositoryAdapter Adapter { get { return adapter; } }

        public ObjectRepository Objects;

        public AppearanceObjectRepository Appearance;

        public MaterialObjectRepository Material;

        public Repository()
        {
            adapter = new PG.CLI.RepositoryAdapter();
            this.Objects = new ObjectRepository(adapter.Objects());
            this.Appearance = new AppearanceObjectRepository();
            this.Material = new MaterialObjectRepository();
        }

        public void New()
        {
        }

        public bool Open(string filename)
        {
            return adapter.Read(filename);
        }

        public bool Save(string filename)
        {
            return adapter.Write(filename);
        }

        public void Import(string filename)
        {

        }

        public void Export(string filename)
        {

        }
    }
}
