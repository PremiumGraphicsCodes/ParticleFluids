using PG.Core.Math;
using Prism.Mvvm;

namespace PG.Control
{
    public class Box3dViewModel : BindableBase
    {
        private Vector3dViewModel minViewModel;
        private Vector3dViewModel maxViewModel;

        public Vector3dViewModel MinViewModel { get { return minViewModel; } }

        public Vector3dViewModel MaxViewModel { get { return maxViewModel; } }

        public Box3dViewModel()
        {
            this.minViewModel = new Vector3dViewModel();
            this.maxViewModel = new Vector3dViewModel();
            this.maxViewModel.Vector = new Vector3d(1, 1, 1);
        }

        public Box3d Box
        {
            get { return new Box3d(minViewModel.Vector, maxViewModel.Vector); }
        }
    }
}
