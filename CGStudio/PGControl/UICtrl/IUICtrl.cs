using PG.Core.Math;
using System.Windows.Input;

namespace PG.CGStudio.UICtrl
{
    public interface IUICtrl
    {
        void OnLeftButtonDown(Vector2d position);

        void OnLeftButtonDragging(Vector2d position);

        void OnLeftButtonUp(Vector2d position);

        void OnRightButtonDown(Vector2d position);

        void OnRightButtonDragging(Vector2d position);

        void OnRightButtonUp(Vector2d position);

        void OnMiddleButtonDown(Vector2d position);

        void OnMiddleButtonDragging(Vector2d position);

        void OnMiddleButtonUp(Vector2d position);

        void OnWheel(double dx);

        void OnKeyDown(Key key);

        void OnKeyUp(Key key);
    }

}
