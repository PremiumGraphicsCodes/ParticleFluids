using PG.Control.Graphics;
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

        public LightEditViewModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var world = MainModel.Instance.World;
            world.Scenes.SetLightScene(PointLightViewModel.Value, Name.Value, Id.Value);
            Canvas3d.Instance.Update(world);
            Canvas3d.Instance.Render();
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
            command.Execute(MainModel.Instance.World.Adapter);
            var name = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
            Id.Value = id;
            Name.Value = name;

            var light = MainModel.Instance.World.Scenes.GetLightScene(id);
            PointLightViewModel.Value = light;
        }
    }
}
