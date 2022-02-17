﻿using PG.Core;
using Reactive.Bindings;
using System;
using System.Collections.Generic;

namespace PG.Scene
{
    public class SceneModel
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public ReactiveProperty<bool> IsSelected { get; }

        public SceneType SceneType { get; set; }
            = new SceneType();

        public List<SceneModel> Children { get; }
            = new List<SceneModel>();

        /*
        public ShapeType Type
        {
            get { return Adapter.GetType(); }
        }
        */

        public SceneModel()
        {
            Id = new ReactiveProperty<int>();
            Name = new ReactiveProperty<string>();
            IsVisible = new ReactiveProperty<bool>();
            IsVisible.Subscribe(OnVisibleChanged);
            IsSelected = new ReactiveProperty<bool>();
        }

        private void OnNameChanged(string str)
        {
            //            Adapter.SetName(str);
        }

        private void OnVisibleChanged(bool b)
        {
            /*
            if (Canvas3d.Instance == null)
            {
                return;
            }
            //            PG.CLI.Command.Set(MainModel.Instance.World.Adapter, PG.GetLabels.IsVisibleLabel, Id.Value, b);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
            */
        }

    }
}