using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FluidStudio
{
    public class TimeLineViewModel : BindableBase
    {
        public ReactiveProperty<int> TimeStep { get; }

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand StopCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ResetCommand { get; }
            = new ReactiveCommand();

        private readonly MainModel mainModel;

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        private bool isStop = false;

        public TimeLineViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.mainModel = mainModel;
            this.scenes = scenes;
            this.canvas = canvas;
            this.TimeStep = mainModel.PhysicsModel.TimeStep;
            StartCommand.Subscribe(() => OnStart());
            StopCommand.Subscribe(() => OnStop());
            ResetCommand.Subscribe(() => OnReset());
        }

        private void OnStart()
        {
            isStop = false;
            Task.Run(() => Simulate());
        }

        private void OnStop()
        {
            isStop = true;
        }

        private void Simulate()
        {
            while(!isStop)
            {
                mainModel.PhysicsModel.Simulate(scenes, mainModel.VDBModel, canvas);
                /*
                //mainModel.Scenes.Export(filePath);
                if (DoOutput.Value)
                {
                    mainModel.PhysicsModel.ExportMesh(scenes, vdb, OutputDirectoryPath.Value);
                }
                */
            }
        }

        private void OnReset()
        {
            mainModel.PhysicsModel.Reset(scenes, mainModel.VDBModel, canvas);
            //mainModel.PhysicsModel.Reset();
        }
    }
}
