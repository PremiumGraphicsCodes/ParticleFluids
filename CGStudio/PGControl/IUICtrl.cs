using PG.Core.Math;
using System.Windows.Input;

namespace PG.CGStudio.UICtrl
{
    public abstract class IUICtrl
    {
        public virtual void OnLeftButtonDown(Vector2d position) { }

        public virtual void OnLeftButtonDragging(Vector2d position) { }

        public virtual void OnLeftButtonUp(Vector2d position) { }

        public virtual void OnRightButtonDown(Vector2d position) { }

        public virtual void OnRightButtonDragging(Vector2d position) { }

        public virtual void OnRightButtonUp(Vector2d position) { }

        public virtual void OnMiddleButtonDown(Vector2d position) { }

        public virtual void OnMiddleButtonDragging(Vector2d position) { }

        public virtual void OnMiddleButtonUp(Vector2d position) { }

        public virtual void OnWheel(double dx) { }

        public virtual void OnKeyDown(Key key) { }

        public virtual void OnKeyUp(Key key) { }
    }

}
