using PG.Control;
using Prism.Mvvm;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class BoxGenerationViewModel : BindableBase
    {
        private readonly Box3dViewModel boxViewModel;

        public Box3dViewModel BoxViewModel
        {
            get { return boxViewModel; }
        }

        public BoxGenerationViewModel()
        {
            this.boxViewModel = new Box3dViewModel();
        }
    }
}
