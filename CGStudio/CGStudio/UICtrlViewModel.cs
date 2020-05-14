using PG.CGStudio.UICtrl;
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
            HwndHostPresenter3d.Instance.Canvas.UICtrl = new CameraUICtrl();
        }

        private void OnPickUICtrl()
        {
            HwndHostPresenter3d.Instance.Canvas.UICtrl = new PickUICtrl(10, Core.SceneType.AllScene);
        }
    }
}
