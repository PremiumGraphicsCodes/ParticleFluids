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
    }
}
