using PG.CGStudio;
using PG.CGStudio.UICtrl;
using PG.Core.Math;
using System;
using System.Windows.Input;

namespace PG.Control.OpenGL
{
    public class Canvas3d : IUICtrl
    {
        private CGStudio.UICtrl.IUICtrl ctrl;
        public CGStudio.UICtrl.IUICtrl UICtrl
        {
            get { return ctrl; }
            set { this.ctrl = value; }
        }

        private PG.CLI.Renderer renderer;
        public PG.CLI.Renderer Renderer { get { return renderer; } }

        public Canvas3d()
        {
            this.ctrl = new CGStudio.UICtrl.CameraUICtrl();
        }

        public void CreateRenderer(System.IntPtr handle, World world)
        {
            renderer = new PG.CLI.Renderer(handle, World.Instance.Adapter);
            this.renderer.Build(world.Adapter);
        }

        public void OnLeftButtonDown(Vector2d position)
        {
            this.ctrl.OnLeftButtonDown(position);
        }

        public void OnLeftButtonDragging(Vector2d position)
        {
            this.ctrl.OnLeftButtonDragging(position);
        }

        public void OnLeftButtonUp(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnRightButtonDown(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnRightButtonDragging(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnRightButtonUp(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnMiddleButtonDown(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnMiddleButtonDragging(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnMiddleButtonUp(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnWheel(double dx)
        {
            throw new NotImplementedException();
        }

        public void OnKeyDown(Key key)
        {
            throw new NotImplementedException();
        }

        public void OnKeyUp(Key key)
        {
            this.UICtrl.OnKeyUp(key);
        }
    }

}
