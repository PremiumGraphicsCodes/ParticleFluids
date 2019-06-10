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
            OpenGLPresenter.Instance.UICtrl = new CameraUICtrl(OpenGLPresenter.Instance.Renderer.camera);
        }

        private void OnPickUICtrl()
        {
            OpenGLPresenter.Instance.UICtrl = new ObjectPickUICtrl();
        }
    }
}
