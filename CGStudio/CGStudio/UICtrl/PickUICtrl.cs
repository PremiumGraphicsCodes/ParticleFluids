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

            var pickedId = Canvas3d.Instance.GetObjectId(position);
            var parentId = pickedId.parentId;

            if (parentId != 0)
            {
                var command = new PG.CLI.Command();
                command.Create(PG.ShapeSelectLabels.CommandNameLabel);
                command.SetArg(PG.ShapeSelectLabels.ShapeIdLabel, parentId);
                command.Execute(model);
                Canvas3d.Instance.Update(MainModel.Instance.World);
                Canvas3d.Instance.Render();

//                var selectedType = CLI.Command.Get(model, "SceneTypeId", parentId);// model.GetTypeById(id.parentId);
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
