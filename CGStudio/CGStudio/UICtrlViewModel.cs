using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class UIControlViewModel
    {
        public ReactiveCommand CameraUICtrlCommand { get; }

        public ReactiveCommand PickUICtrlCommand { get; }

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public UIControlViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.CameraUICtrlCommand = new ReactiveCommand();
            this.CameraUICtrlCommand.Subscribe(OnCameraUICtrl);
            this.PickUICtrlCommand = new ReactiveCommand();
            this.PickUICtrlCommand.Subscribe(OnPickUICtrl);
        }

        private void OnCameraUICtrl()
        {
            canvas.UICtrl = new CameraUICtrl(world, canvas);
        }

        private void OnPickUICtrl()
        {
            canvas.UICtrl = new PickUICtrl(world, canvas, 10, Core.SceneType.AllScene);
        }
    }
}
