using PG.Core.Shape;

namespace PG.CGStudio
{
    public class Repository
    {
        private PG.CLI.RepositoryAdapter adapter;

        public PG.CLI.RepositoryAdapter Adapter { get { return adapter; } }

        public PG.Core.Scene scene;

        public PG.Core.Scene Scene { get { return scene; } }

        public Repository()
        {
            this.adapter = new PG.CLI.RepositoryAdapter();
            this.scene = new PG.Core.Scene(0, "Root", Core.SceneType.Root);
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
