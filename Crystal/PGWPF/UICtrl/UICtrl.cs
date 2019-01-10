using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public abstract class UICtrl
    {
        public virtual void OnLeftButtonDown(Vector2d position) { }

        public virtual void OnLeftButtonDragging(Vector2d position) { }

        public virtual void OnLeftButtonUp(Vector2d position) { }

        public virtual void OnRightButtonDown(Vector2d position) { }

        public virtual void OnRightButtonDragging(Vector2d position) { }

        public virtual void OnRightButtonUp(Vector2d position) { }
    }

}
