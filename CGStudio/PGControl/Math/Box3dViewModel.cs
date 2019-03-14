using PG.Core.Math;
using Prism.Mvvm;

namespace PG.Control
{
    public class Box3dViewModel : BindableBase
    {
        public Vector3dViewModel MinViewModel { get; }
            = new Vector3dViewModel();

        public Vector3dViewModel MaxViewModel { get; }
            = new Vector3dViewModel();

        public Box3dViewModel()
        {
            this.MinViewModel.Value = new Vector3d(0, 0, 0);
            this.MaxViewModel.Value = new Vector3d(1, 1, 1);
        }

        public Box3d Value
        {
            get { return new Box3d(MinViewModel.Value, MaxViewModel.Value); }
        }
    }
}
