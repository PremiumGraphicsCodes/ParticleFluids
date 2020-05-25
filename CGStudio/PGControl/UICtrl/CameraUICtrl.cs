using System.Windows.Input;
using PG.Control.OpenGL;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class CameraUICtrl : IUICtrl
    {
        private Vector2d prevPosition;

        private readonly World world;

        private readonly Canvas3d canvas;

        public CameraUICtrl(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.prevPosition = new Vector2d();
        }

        public void OnKeyDown(Key key)
        {
            throw new System.NotImplementedException();
        }

        public void OnKeyUp(Key key)
        {
            throw new System.NotImplementedException();
        }

        public void OnLeftButtonDown(Vector2d position)
        {
            prevPosition = position;
        }

        public void OnLeftButtonDragging(Vector2d position)
        {
            var matrix = canvas.Camera.GetRotationMatrix();

            var diff = position - prevPosition;
            //
            var bb = world.Scenes.GetBoundingBox(0);
            //var scale = bb.Min.Distance(bb.Max) * 0.1;
            var v = new Vector4d(diff.X, diff.Y, 0.0, 0.0) * matrix.Transposed();
            canvas.Camera.Translate(new Vector3d(v.X, v.Y, v.Z));
            canvas.Render();
            prevPosition = position;
        }

        public void OnLeftButtonUp(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonDown(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonDragging(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonUp(Vector2d position)
        {
            ;
        }

        public void OnRightButtonDown(Vector2d position)
        {
            this.prevPosition = position;
        }

        public void OnRightButtonDragging(Vector2d position)
        {
            var matrix = canvas.Camera.GetRotationMatrix();

            var diff = position - prevPosition;
            var v = new Vector4d(diff.Y, diff.X, 0.0, 0.0) * matrix.Transposed();
            var matrix1 = Matrix3d.RotationX(v.X);
            var matrix2 = Matrix3d.RotationY(v.Y);
            var matrix3 = Matrix3d.RotationZ(v.Z);

            var m = matrix3 * matrix2 * matrix1;
            canvas.Camera.Rotate(m);

            canvas.Render();
            prevPosition = position;
        }

        public void OnRightButtonUp(Vector2d position)
        {
            ;
        }

        public void OnWheel(double dx)
        {
            canvas.Camera.Zoom((float)dx);
            canvas.Render();
        }
    }
}
