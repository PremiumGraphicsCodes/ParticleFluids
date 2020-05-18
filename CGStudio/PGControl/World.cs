using PG.Scene;
using PG.Control;

namespace PG.CGStudio
{
    public class World
    {
        private PG.CLI.WorldAdapter adapter;

        public PG.CLI.WorldAdapter Adapter { get { return adapter; } }

        public SceneListModel Scenes { get; }

        public static World Instance;

        private World()
        {
            this.adapter = new PG.CLI.WorldAdapter();
            this.Scenes = new SceneListModel(adapter);
        }

        public static void CreateInstance()
        {
            if (Instance == null)
            {
                Instance = new World();
            }
        }

        public void New()
        {
            /*
            var command = new PG.CLI.Command(NewLabels.CommandNameLabel);

            Renderer.Bind();
            command.Execute(adapter);
            Renderer.UnBind();

            this.Scenes.Sync();
            */
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
