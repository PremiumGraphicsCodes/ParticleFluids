using PG.CGStudio.Scene;
using PG.CGStudio.Scene.Item;
using PG.Core;
using PG.Core.Math;

namespace PG.CGStudio
{
    public class World
    {
        private PG.CLI.WorldAdapter adapter;
        public PG.CLI.WorldAdapter Adapter { get { return adapter; } }

        public SceneListModel Scenes { get; }

        public ItemListModel Items { get; }

        public World()
        {
            this.adapter = new PG.CLI.WorldAdapter();
            this.Scenes = new SceneListModel(adapter);
            this.Items = new ItemListModel(adapter);
        }

        public void New()
        {
            var command = new PG.CLI.Command(NewLabels.CommandNameLabel);

            Canvas3d.Instance.Renderer.Bind();
            command.Execute(adapter);
            Canvas3d.Instance.Renderer.UnBind();

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

        public Vector3d GetPosition(ObjectId id)
        {
            return PG.CLI.Command.Get<Vector3d>(adapter, PG.GetLabels.PositionLabel, id.parentId, id.childId);
        }
    }
}
