using PG.Core.Math;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectPickUICtrl : IUICtrl
    {
        private List<ObjectModel> pickedObjects;
        private int mergin;
        private Action<int> action;

        public Action<int> Action
        {
            set { this.action = value; }
        }

        public ObjectPickUICtrl(int mergin)
        {
            this.mergin = mergin;
            this.pickedObjects = new List<ObjectModel>();
        }

        public List<ObjectModel> PickedObjects
        {
            get { return pickedObjects; }
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            position.Y = 1.0 - position.Y;
            var id = Canvas3d.Instance.Renderer.Pick(position, mergin);
            if(id.parentId != 0)
            {
                var model = MainModel.Instance.Repository.Objects;
                var selectedItem = model.FindObjectById(id.parentId);
                if (selectedItem == null)
                {
                    return;
                }
                pickedObjects.Add(selectedItem);

                if (action != null)
                {
                    action(id.parentId);
                }

                /*
                var parameters = new NavigationParameters
                {
                    { "Object", selectedItem }
                };
                MainWindowViewModel.Instance.NavigateWithParam("Object", parameters);
                */
            }
        }
    }
}
