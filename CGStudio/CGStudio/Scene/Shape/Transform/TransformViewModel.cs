using PG.Control.Math;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase
    {
        public Matrix4dViewModel MatrixViewModel { get; }
            = new Matrix4dViewModel();
        
        public TransformViewModel(SceneList world, Canvas3d canvas)
        {
        }
    }
}
