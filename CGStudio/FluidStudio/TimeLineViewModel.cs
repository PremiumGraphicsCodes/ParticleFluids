using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Threading.Tasks;

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

        private readonly MainModel mainModel;

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        private bool isStop = false;

        public TimeLineViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.mainModel = mainModel;
            this.scenes = scenes;
            this.canvas = canvas;
            StartCommand.Subscribe(() => OnStart(mainModel, scenes));
            StopCommand.Subscribe(() => OnStop());
        }

        private void OnStart(MainModel mainModel, SceneList sceneList)
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
                mainModel.PhysicsModel.Simulate(scenes, canvas);
                TimeStep.Value++;
            }
        }
    }
}
