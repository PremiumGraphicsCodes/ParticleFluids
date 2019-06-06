using PG.Core.Shape;

namespace PG.CGStudio
{
    public class Repository
    {
        private PG.CLI.RepositoryAdapter adapter;

        public PG.CLI.RepositoryAdapter Adapter { get { return adapter; } }

        public ObjectRepository Objects;

        public AppearanceObjectRepository Appearance;

        public Material.MaterialObjectRepository Material;

        public Light.LightObjectRepository Light;

        public Texture.TextureObjectRepository Texture;

        public Repository()
        {
            this.adapter = new PG.CLI.RepositoryAdapter();
            this.Objects = new ObjectRepository(adapter.Objects());
            this.Appearance = new AppearanceObjectRepository(adapter.Appearance());
            this.Material = new Material.MaterialObjectRepository(adapter.Appearance().Material());
            this.Light = new Light.LightObjectRepository();
            this.Texture = new Texture.TextureObjectRepository();
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
