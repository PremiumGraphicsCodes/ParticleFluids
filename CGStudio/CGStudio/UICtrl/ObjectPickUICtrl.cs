using PG.Core.Math;
using Prism.Regions;
using System.Collections.Generic;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectPickUICtrl : IUICtrl
    {
        private List<ObjectModel> pickedObjects;
        private int mergin;

        public ObjectPickUICtrl(int mergin)
        {
            this.mergin = mergin;
            pickedObjects = new List<ObjectModel>();
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            position.Y = 1.0 - position.Y;
            var id = OpenGLPresenter.Instance.Renderer.Pick(position, mergin);
            if(id.parentId != 0)
            {
                var model = MainModel.Instance.Repository.Objects;
                var selectedItem = model.FindObjectById(id.parentId);
                if (selectedItem == null)
                {
                    return;
                }
                pickedObjects.Add(selectedItem);
                var parameters = new NavigationParameters
                {
                    { "Object", selectedItem }
                };
                MainWindowViewModel.Instance.NavigateWithParam("Object", parameters);
            }
        }
    }
}
