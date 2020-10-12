using PG;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio
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

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public CameraControlViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            XYCommand.Subscribe(OnXY);
            YZCommand.Subscribe(OnYZ);
            ZXCommand.Subscribe(OnZX);
            XYZCommand.Subscribe(OnXYZ);
            FitCommand.Subscribe(OnFit);
        }

        private void OnXY()
        {
            canvas.Camera.SetXY();
            canvas.Render();
        }

        private void OnYZ()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraYZCommandLabel);
            command.Execute(world.Adapter);
            canvas.Render();
        }

        private void OnZX()
        {
            var command = new PG.CLI.Command(CameraLabels.CameraZXCommandLabel);
            command.Execute(world.Adapter);
            canvas.Render();
        }

        private void OnXYZ()
        {

        }

        private void OnFit()
        {
            canvas.Camera.Fit();
            canvas.Render();
        }
    }
}
