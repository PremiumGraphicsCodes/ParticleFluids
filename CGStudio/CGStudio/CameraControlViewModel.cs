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
            World.Instance.Camera.SetXY();
            Canvas3d.Instance.Render();
        }

        private void OnYZ()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraYZCommandLabel);
            command.Execute(World.Instance.Adapter);
            Canvas3d.Instance.Render();
        }

        private void OnZX()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraZXCommandLabel);
            command.Execute(World.Instance.Adapter);
            Canvas3d.Instance.Render();

        }

        private void OnXYZ()
        {

        }

        private void OnFit()
        {
            World.Instance.Camera.Fit();
            Canvas3d.Instance.Render();
        }
    }
}
