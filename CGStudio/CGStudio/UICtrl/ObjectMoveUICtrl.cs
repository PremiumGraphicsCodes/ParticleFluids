using PG.Core.Math;
using Prism.Regions;
using System.Collections.Generic;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectMoveUICtrl : IUICtrl
    {
        private Vector2d prevPos;

        private List<ObjectModel> Objects;

        public ObjectMoveUICtrl()
        {
            Objects = new List<ObjectModel>();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            this.prevPos = position;
        }

        public override void OnLeftButtonUp(Vector2d position)
        {

        }

        public override void OnLeftButtonDragging(Vector2d position)
        {
            this.prevPos = position;
        }

    }
}
