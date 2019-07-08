using Reactive.Bindings;

namespace PG.CGStudio
{
    public class SceneListViewModel
    {
        public ReadOnlyReactiveCollection<PG.Core.Scene> Items { get; }

        public SceneListViewModel()
        {
            Items = MainModel.Instance.Repository.Scene.ToReadOnlyReactiveCollection();
        }
    }
}
