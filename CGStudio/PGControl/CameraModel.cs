using PG.Core.Math;

namespace PG.Control
{
    public class CameraModel
    {
        private readonly PG.CLI.WorldAdapter adapter;

        public CameraModel(PG.CLI.WorldAdapter adapter)
        {
            this.adapter = adapter;
        }

        public void SetXY()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraXYCommandLabel);
            command.Execute(adapter);
        }

        public void SetYZ()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraYZCommandLabel);
            command.Execute(adapter);
        }

        public void SetZX()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraZXCommandLabel);
            command.Execute(adapter);
        }

        public void Fit()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraFitCommandLabel);
            command.Execute(adapter);
        }

        public void Translate(Vector3d v)
        {
            var command = new PG.CLI.Command(CameraLabels.CameraTranslateCommandLabel);
            command.SetArg(PG.CameraLabels.TranslateLabel, new Vector3d(v.X, v.Y, v.Z));
            command.Execute(adapter);
        }

        public Matrix4d GetRotationMatrix()
        {
            var command = new PG.CLI.Command(PG.CameraGetLabels.CommandNameLabel);
            command.Execute(adapter);
            return command.GetResult<Matrix4d>(PG.CameraGetLabels.RotationMatrixLabel);
        }
    }
}
