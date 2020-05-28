using PG.Control.OpenGL;
using PG.Core;
using PG.Core.Math;
using PG.Scene;
using System;
using System.Collections.Generic;
using System.Windows.Input;
using Labels = PG.PickLabels;

namespace PG.CGStudio.UICtrl
{
    public class PickUICtrl : IUICtrl
    {
        private List<ObjectId> pickedIds = new List<ObjectId>();
        private int mergin;
        private List<Action<ObjectId>> actions = new List<Action<ObjectId>>();
        private SceneType type;
        private readonly SceneListModel world;
        private readonly Canvas3d canvas;

        public PickUICtrl(SceneListModel world, Canvas3d canvas, int mergin, SceneType type)
        {
            this.world = world;
            this.canvas = canvas;
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

        public void OnKeyDown(Key key)
        {
            ;
        }

        public void OnKeyUp(Key key)
        {
            ;
        }

        public void OnLeftButtonDown(Vector2d position)
        {
            var pickedId = canvas.GetObjectId(position);
            var parentId = pickedId.parentId;

            if (parentId != 0)
            {
                var command = new PG.CLI.Command();
                command.Create(PG.ShapeSelectLabels.CommandNameLabel);
                command.SetArg(PG.ShapeSelectLabels.ShapeIdLabel, parentId);
                command.Execute(world.Adapter);
                //command.GetResult<int>(PG.ShapeSelectLabels.BoundingBoxItemIdLabel);
                canvas.Update();
                canvas.Render();

                pickedIds.Add(pickedId);

                foreach (var a in actions)
                {
                    a(pickedId);
                }
            }

        }

        public void OnLeftButtonDragging(Vector2d position)
        {
            throw new NotImplementedException();
        }

        public void OnLeftButtonUp(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonDown(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonDragging(Vector2d position)
        {
            ;
        }

        public void OnMiddleButtonUp(Vector2d position)
        {
            ;
        }

        public void OnRightButtonDown(Vector2d position)
        {
            ;
        }

        public void OnRightButtonDragging(Vector2d position)
        {
            ;
        }

        public void OnRightButtonUp(Vector2d position)
        {
            ;
        }

        public void OnWheel(double dx)
        {
            ;
        }
    }
}
