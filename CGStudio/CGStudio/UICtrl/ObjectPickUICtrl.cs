using PG.Core.Math;
using Prism.Regions;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectPickUICtrl : IUICtrl
    {
        public override void OnLeftButtonDown(Vector2d position)
        {
            position.Y = 1.0 - position.Y;
            var id = OpenGLPresenter.Instance.Renderer.Pick(position, 10);
            if(id.parentId != 0)
            {
                var model = MainModel.Instance.Repository.Objects;
                var selectedItem = model.FindObjectById(id.parentId);
                if (selectedItem == null)
                {
                    return;
                }
                var parameters = new NavigationParameters
                {
                    { "Object", selectedItem }
                };
                MainWindowViewModel.Instance.NavigateWithParam("Object", parameters);
            }
        }
    }
}
