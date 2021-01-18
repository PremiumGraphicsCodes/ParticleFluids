using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Tool.Modeling
{
    public class VolumeToPSViewModel
    {
        public SceneSelectViewModel VolumeSelectViewModel { get; }

        public SceneSelectViewModel PSSelectViewModel { get; }

        public VolumeToPSViewModel(SceneList scenes, Canvas3d canvas)
        {
            VolumeSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            PSSelectViewModel = new SceneSelectViewModel(scenes, canvas);
        }
    }
}
