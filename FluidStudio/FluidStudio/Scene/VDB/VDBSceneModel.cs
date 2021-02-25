using PG.Scene;
using Reactive.Bindings;

namespace FluidStudio.Scene.VDB
{
    public class VDBSceneModel : SceneModel
    {
        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>("");
    }
}
