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

        private readonly MainModel mainModel;

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        public TimeLineViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.mainModel = mainModel;
            this.scenes = scenes;
            this.canvas = canvas;
            StartCommand.Subscribe(() => OnStart(mainModel, scenes));
        }


        private void OnStart(MainModel mainModel, SceneList sceneList)
        {
            for (int i = 0; i < 100; ++i)
            {
                Simulate();
            }
        }

        private void Simulate()
        {
            var pScenes = mainModel.PhysicsModel.Scenes;
            foreach (var ps in pScenes)
            {
                ps.Simulate(scenes);
                ps.SendShader(scenes, canvas);
            }
        }
    }
}
