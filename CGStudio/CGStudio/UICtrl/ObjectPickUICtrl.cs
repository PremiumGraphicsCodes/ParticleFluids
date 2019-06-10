using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class ObjectPickUICtrl : IUICtrl
    {
        public override void OnLeftButtonDown(Vector2d position)
        {
            var id = OpenGLPresenter.Instance.Renderer.Pick(position);
            if(id.parentId != 0)
            {
                ;
            }
        }
    }
}
