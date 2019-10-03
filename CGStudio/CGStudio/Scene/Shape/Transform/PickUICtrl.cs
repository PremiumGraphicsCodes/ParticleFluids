using PG.Core;
using PG.Core.Math;
using System;
using System.Collections.Generic;

namespace PG.CGStudio.UICtrl
{
    public class PickUICtrl : IUICtrl
    {
        private List<ObjectId> pickedIds;
        private int mergin;
        private Action<ObjectId> action;
        private SceneType type;

        public Action<ObjectId> Action
        {
            set { this.action = value; }
        }

        public PickUICtrl(int mergin, SceneType type)
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
            var model = MainModel.Instance.Repository.Adapter;

            Canvas3d.Instance.Renderer.Bind();
            var command = new PG.CLI.Command("PickCommand");
            command.SetArg("Position", position.X, 1.0 - position.Y);
            command.Execute(model);
            var parentId = command.GetResult<int>("ParentId");
            Canvas3d.Instance.Renderer.UnBind();

            if (parentId != 0)
            {
                var selectedType = CLI.Command.Get(model, parentId, "SceneTypeId");// model.GetTypeById(id.parentId);
                /*
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
