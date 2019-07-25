﻿using PG.CGStudio.UICtrl;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class UIControlViewModel
    {
        public ReactiveCommand CameraUICtrlCommand { get; }

        public ReactiveCommand PickUICtrlCommand { get; }

        public UIControlViewModel()
        {
            this.CameraUICtrlCommand = new ReactiveCommand();
            this.CameraUICtrlCommand.Subscribe(OnCameraUICtrl);
            this.PickUICtrlCommand = new ReactiveCommand();
            this.PickUICtrlCommand.Subscribe(OnPickUICtrl);
        }

        private void OnCameraUICtrl()
        {
            Canvas3d.Instance.UICtrl = new CameraUICtrl(Canvas3d.Instance.Renderer.camera);
        }

        private void OnPickUICtrl()
        {
            Canvas3d.Instance.UICtrl = new ObjectPickUICtrl(10, Core.SceneType.AllScene);
        }
    }
}
