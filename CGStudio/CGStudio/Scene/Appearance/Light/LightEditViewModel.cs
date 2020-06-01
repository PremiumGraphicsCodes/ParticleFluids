using PG.Control.Graphics;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Light
{
    public class LightEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public PointLightViewModel PointLightViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public LightEditViewModel(SceneList world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            world.SetLightScene(PointLightViewModel.Value, Name.Value, Id.Value);
            canvas.Update();
            canvas.Render();
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {

        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var id = (int)navigationContext.Parameters["Id"];
            var command = new PG.CLI.Command();
            command.SetArg(PG.SceneGetLabels.IdLabel, id);
            command.Execute(world.Adapter);
            var name = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
            Id.Value = id;
            Name.Value = name;

            var light = world.GetLightScene(id);
            PointLightViewModel.Value = light;
        }
    }
}
