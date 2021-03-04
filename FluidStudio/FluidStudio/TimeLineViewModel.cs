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
            = new ReactiveProperty<int>(0);

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand StopCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ResetCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<int> StartTimeStep { get; }
            = new ReactiveProperty<int>(0);

        public ReactiveProperty<int> EndTimeStep { get; }
            = new ReactiveProperty<int>(240);

        //public ReactiveProperty<int> CurrentTimeStep { get; }
        //    = new ReactiveProperty<int>(0);

        private readonly MainModel mainModel;

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        private bool isStop = false;

        public TimeLineViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.mainModel = mainModel;
            this.scenes = scenes;
            this.canvas = canvas;
            //this.CurrentTimeStep = mainModel.PhysicsModel.TimeStep;
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
                TimeStep.Value++;

                if (TimeStep.Value > EndTimeStep.Value)
                {
                    isStop = true;
                }
            }
        }

        private void OnReset()
        {
            if(!isStop)
            {
                return;
            }
            mainModel.PhysicsModel.Reset(scenes, mainModel.FileIOModel, mainModel.VDBModel, canvas);
            TimeStep.Value = 0;
        }
    }
}
