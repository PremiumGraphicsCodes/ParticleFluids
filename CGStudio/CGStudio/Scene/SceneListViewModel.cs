using Reactive.Bindings;
using PG.Scene;

namespace PG.CGStudio
{
    public class SceneListViewModel
    {
        public ReadOnlyReactiveCollection<SceneModel> Items { get; }

        public SceneListViewModel()
        {
            Items = World.Instance.Scenes.Scenes.ToReadOnlyReactiveCollection();
        }
    }
}
