using PG.Core;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class SceneListViewModel
    {
        public ReadOnlyReactiveCollection<Scene> Items { get; }
        //public ReactiveCollection<Scene> Items { get; }

        public SceneListViewModel()
        {
            Items = MainModel.Instance.Repository.Scene.ToReadOnlyReactiveCollection();
            //var scene = new Scene(0, "Root", SceneType.Root);
            //scene.Children.Add(new Scene(1, "Child", SceneType.ParticleSystem));
            //Items = new ReactiveCollection<Scene>();
            //Items.Add(scene);
        }
    }
}
