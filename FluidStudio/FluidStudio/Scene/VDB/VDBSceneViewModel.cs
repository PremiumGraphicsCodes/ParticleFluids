using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Scene.VDB
{
    public class VDBSceneViewModel
    {
        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand FileSelectCommand { get; }
    }
}
