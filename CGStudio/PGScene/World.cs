using PG.Scene;

namespace PG.CGStudio
{
    public class World
    {
        private PG.CLI.WorldAdapter adapter;

        public PG.CLI.WorldAdapter Adapter { get { return adapter; } }

        public SceneListModel Scenes { get; }

        private PG.CLI.Renderer renderer;

        public PG.CLI.Renderer Renderer { get { return renderer; } }

        public static World Instance;

        private World()
        {
            this.adapter = new PG.CLI.WorldAdapter();
            this.Scenes = new SceneListModel(adapter);
        }

        public static void CreateInstance()
        { 
            Instance = new World();
        }

        public void CreateRenderer(System.IntPtr handle)
        {
            renderer = new PG.CLI.Renderer(handle, World.Instance.Adapter);
            this.renderer.Build(Adapter);
        }

        public void New()
        {
            var command = new PG.CLI.Command(NewLabels.CommandNameLabel);

            Renderer.Bind();
            command.Execute(adapter);
            Renderer.UnBind();

            this.Scenes.Sync();
        }

        public bool Open(string filename)
        {
            return false;
        }

        public bool Save(string filename)
        {
            return false;
        }

    }
}
