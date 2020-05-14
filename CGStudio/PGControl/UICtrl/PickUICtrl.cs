using PG.Core;
using PG.Core.Math;
using System;
using System.Collections.Generic;
using Labels = PG.PickLabels;

namespace PG.CGStudio.UICtrl
{
    public class PickUICtrl : IUICtrl
    {
        private List<ObjectId> pickedIds = new List<ObjectId>();
        private int mergin;
        private List<Action<ObjectId>> actions = new List<Action<ObjectId>>();
        private SceneType type;

        public PickUICtrl(int mergin, SceneType type)
        {
            this.mergin = mergin;
            this.type = type;
        }

        public List<ObjectId> PickedIds
        {
            get { return pickedIds; }
        }

        public void AddAction(Action<ObjectId> action)
        {
            actions.Add(action);
        }

        public override void OnLeftButtonDown(Vector2d position)
        {
            var model = World.Instance.Adapter;

            var pickedId = HwndHostPresenter3d.Instance.GetObjectId(position);
            var parentId = pickedId.parentId;

            if (parentId != 0)
            {
                var command = new PG.CLI.Command();
                command.Create(PG.ShapeSelectLabels.CommandNameLabel);
                command.SetArg(PG.ShapeSelectLabels.ShapeIdLabel, parentId);
                command.Execute(model);
                //command.GetResult<int>(PG.ShapeSelectLabels.BoundingBoxItemIdLabel);
                HwndHostPresenter3d.Instance.Update(World.Instance);
                HwndHostPresenter3d.Instance.Render();

                pickedIds.Add(pickedId);

                foreach (var a in actions)
                {
                    a(pickedId);
                }
            }

        }
    }
}
