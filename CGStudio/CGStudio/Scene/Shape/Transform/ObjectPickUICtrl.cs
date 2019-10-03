﻿using PG.Core;
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
            /*
            position.Y = 1.0 - position.Y;
            var id = Canvas3d.Instance.Renderer.Pick(position, mergin);
            if (id.parentId != 0)
            {
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
            }
            */
        }
    }
}
