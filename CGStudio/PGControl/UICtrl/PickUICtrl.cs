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
        private List<SceneId> pickedIds = new List<SceneId>();
        private int mergin;
        private List<Action<SceneId>> actions = new List<Action<SceneId>>();
        private SceneType type;
        private readonly SceneList scene;
        private readonly Canvas3d canvas;

        public PickUICtrl(SceneList scene, Canvas3d canvas, int mergin, SceneType type)
        {
            this.scene = scene;
            this.canvas = canvas;
            this.mergin = mergin;
            this.type = type;
        }

        public List<SceneId> PickedIds
        {
            get { return pickedIds; }
        }

        public void AddAction(Action<SceneId> action)
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
//            var x = position.X * canvas.Width;

            var pickedId = canvas.GetObjectId(position);
            var parentId = pickedId.parentId;

            if (parentId != 0)
            {
                var command = new PG.CLI.Command();
                command.Create(PG.ShapeSelectLabels.CommandNameLabel);
                command.SetArg(PG.ShapeSelectLabels.ShapeIdLabel, parentId);
                command.Execute(scene.Adapter);
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
