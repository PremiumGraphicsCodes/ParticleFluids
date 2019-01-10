using Reactive.Bindings;

namespace PG.CGStudio
{
    public class CameraControlViewModel
    {
        public ReactiveCommand XYCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand YZCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ZXCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand XYZCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand FitCommand { get; }
            = new ReactiveCommand();

        public CameraControlViewModel()
        {
            XYCommand.Subscribe(OnXY);
            YZCommand.Subscribe(OnYZ);
            ZXCommand.Subscribe(OnZX);
            XYZCommand.Subscribe(OnXYZ);
            FitCommand.Subscribe(OnFit);
        }

        private void OnXY()
        {
 //           Canvas3dView.Instance.Renderer.camera.XY
        }

        private void OnYZ()
        {

        }

        private void OnZX()
        {

        }

        private void OnXYZ()
        {

        }

        private void OnFit()
        {

        }
    }
}
