using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class ParticleSystemGenerationViewModel
    {
        public SphereGenerationViewModel SphereGenerationViewModel { get; }

        public BoxGenerationViewModel BoxGenerationViewModel { get; }

        public ParticleSystemGenerationViewModel()
        {
            this.SphereGenerationViewModel = new SphereGenerationViewModel();
            this.BoxGenerationViewModel = new BoxGenerationViewModel();
        }
    }
}
