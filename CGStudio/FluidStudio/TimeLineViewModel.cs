using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;

namespace FluidStudio
{
    public class TimeLineViewModel : BindableBase
    {
        public ReactiveProperty<int> Step { get; }
            = new ReactiveProperty<int>(0);

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        public TimeLineViewModel(MainModel mainModel, SceneList scenes)
        {
            StartCommand.Subscribe(() => OnStart(mainModel, scenes));
        }

        private void OnStart(MainModel mainModel, SceneList sceneList)
        {
            var scenes = mainModel.PhysicsModel.Scenes;
            foreach(var scene in scenes)
            {
                scene.Simulate(sceneList);
            }
        }
    }
}
