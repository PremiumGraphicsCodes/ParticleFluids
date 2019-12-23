using PG.Control.Graphics;
using PG.Core.Graphics;
using PG.Core.Math;
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
            var repository = MainModel.Instance.World;
//            repository.UpdateLightScene(Id.Value, PointLightViewModel.Value);
            Canvas3d.Instance.Update(repository);
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
            var name = PG.CLI.Command.Get<string>(MainModel.Instance.World.Adapter, PG.GetLabels.NameLabel, id);
            Id.Value = id;
            Name.Value = name;

            var light = new PointLight
            {
                Ambient = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.AmbientLabel, id),
                Diffuse = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.DiffuseLabel, id),
                Specular = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.SpecularLabel, id),
                Position = PG.CLI.Command.Get<Vector3d>(MainModel.Instance.World.Adapter, PG.GetLabels.PositionLabel, id),
            };

            PointLightViewModel.Value = light;
        }
    }
}
