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
            var command = new PG.CLI.Command(CameraLabels.CameraXYCommandLabel);
            command.Execute(MainModel.Instance.World.Adapter);
            Canvas3d.Instance.Render();
        }

        private void OnYZ()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraYZCommandLabel);
            command.Execute(MainModel.Instance.World.Adapter);
            Canvas3d.Instance.Render();
        }

        private void OnZX()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraZXCommandLabel);
            command.Execute(MainModel.Instance.World.Adapter);
            Canvas3d.Instance.Render();

        }

        private void OnXYZ()
        {

        }

        private void OnFit()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraFitCommandLabel);
            command.Execute(MainModel.Instance.World.Adapter);
            Canvas3d.Instance.Render();
        }
    }
}
