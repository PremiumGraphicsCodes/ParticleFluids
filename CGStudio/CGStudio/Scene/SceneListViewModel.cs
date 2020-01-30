using Reactive.Bindings;
using PG.Scene;

namespace PG.CGStudio
{
    public class SceneListViewModel
    {
        public ReadOnlyReactiveCollection<SceneModel> Items { get; }

        public SceneListViewModel()
        {
            Items = MainModel.Instance.World.Scenes.Scenes.ToReadOnlyReactiveCollection();
        }
    }
}
