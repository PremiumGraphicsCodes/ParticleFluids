using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Scene.VDB
{
    public class VDBSceneModel : SceneModel
    {
        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>("");
    }
}
