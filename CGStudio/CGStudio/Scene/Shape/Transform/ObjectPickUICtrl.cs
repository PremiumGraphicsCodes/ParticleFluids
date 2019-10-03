using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Windows;

namespace PG.CGStudio.UICtrl
{
    public class ObjectPickUICtrl : IUICtrl
    {
        private List<ObjectId> pickedIds;
        private int mergin;
        private Action<ObjectId> action;
        private SceneType type;

        public Action<ObjectId> Action
        {
            set { this.action = value; }
        }

        public ObjectPickUICtrl(int mergin, SceneType type)
        {
            this.mergin = mergin;
            this.pickedIds = new List<ObjectId>();
            this.type = type;
        }

        public List<ObjectId> PickedIds
        {
            get { return pickedIds; }
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            position.Y = 1.0 - position.Y;

            Canvas3d.Instance.Renderer.Bind();
            var command = new PG.CLI.Command("PickCommand");
            command.SetArg("Position", position.X, position.Y);
            command.Execute(MainModel.Instance.Repository.Adapter);
            var parentId = command.GetResult<int>("ParentId");
            Canvas3d.Instance.Renderer.UnBind();

            if (parentId != 0)
            {
                /*
                var model = MainModel.Instance.Repository;
                var selectedType = model.GetTypeById(id.parentId);
                if (!type.HasFlag(selectedType))
                {
                    return;
                }
                pickedIds.Add(id);

                if (action != null)
                {
                    action(id);
                }
                */
            }
        }
    }
}
