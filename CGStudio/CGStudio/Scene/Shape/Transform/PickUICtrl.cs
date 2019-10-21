using PG.Core;
using PG.Core.Math;
using System;
using System.Collections.Generic;
using Labels = PG.PickLabels;

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
            var model = MainModel.Instance.World.Adapter;

            Canvas3d.Instance.Renderer.Bind();
            var command = new PG.CLI.Command(Labels.PickCommandLabel);
            command.SetArg(Labels.PositionLabel, new Vector2d( position.X, 1.0 - position.Y) );
            command.Execute(model);
            var parentId = command.GetResult<int>(Labels.ParentIdLabel);
            var childId = command.GetResult<int>(Labels.ChildIdLabel);
            Canvas3d.Instance.Renderer.UnBind();

            if (parentId != 0)
            {
                var selectedType = CLI.Command.Get(model, "SceneTypeId", parentId);// model.GetTypeById(id.parentId);
                var pickedId = new ObjectId();
                pickedId.parentId = parentId;
                pickedId.childId = childId;
                pickedIds.Add(pickedId);

                if (action != null)
                {
                    action(pickedId);
                }
                /*
                if (!type.HasFlag(selectedType))
                {
                    return;
                }
                pickedIds.Add(id);

                */
            }
        }
    }
}
