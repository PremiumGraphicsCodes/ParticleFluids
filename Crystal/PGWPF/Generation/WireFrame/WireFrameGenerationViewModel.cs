using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Generation.WireFrame
{
    public class WireFrameGenerationViewModel
    {
        public BoxGenerationViewModel BoxGenerationViewModel { get; }

        public WireFrameGenerationViewModel()
        {
            this.BoxGenerationViewModel = new BoxGenerationViewModel();
        }
    }
}
