using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Threading.Tasks;

namespace FluidStudio
{
    public class TimeLineViewModel : BindableBase
    {
        public ReactiveProperty<int> Step { get; }
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
            /*
            for (int i = 0; i < 100; ++i)
            {
                Simulate();
            }
            */
        }

        private void OnStop()
        {
            isStop = true;
        }

        private void Simulate()
        {
            while(!isStop)
            {
                SimulateNext();
            }
        }

        private void SimulateNext()
        {
            var pScenes = mainModel.PhysicsModel.Scenes;
            foreach (var ps in pScenes)
            {
                ps.Simulate(scenes);
                foreach(var fluid in ps.Fluids)
                {
                    canvas.SendShader(scenes, fluid.Id);
                }
                canvas.Render();
            }
        }
    }
}
