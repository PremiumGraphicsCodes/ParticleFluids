using Reactive.Bindings;

namespace FluidStudio.Scene.VDB
{
    public class VDBSceneViewModel
    {
        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand FileSelectCommand { get; }
    }
}
