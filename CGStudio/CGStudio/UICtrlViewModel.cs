using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class UIControlViewModel
    {
        public ReactiveCommand CameraUICtrlCommand { get; }

        public ReactiveCommand PickUICtrlCommand { get; }

        public UIControlViewModel(World world)
        {
            this.CameraUICtrlCommand = new ReactiveCommand();
            this.CameraUICtrlCommand.Subscribe(OnCameraUICtrl);
            this.PickUICtrlCommand = new ReactiveCommand();
            this.PickUICtrlCommand.Subscribe(() => OnPickUICtrl(world));
        }

        private void OnCameraUICtrl()
        {
            Canvas3d.Instance.UICtrl = new CameraUICtrl();
        }

        private void OnPickUICtrl(World world)
        {
            Canvas3d.Instance.UICtrl = new PickUICtrl(world, 10, Core.SceneType.AllScene);
        }
    }
}
