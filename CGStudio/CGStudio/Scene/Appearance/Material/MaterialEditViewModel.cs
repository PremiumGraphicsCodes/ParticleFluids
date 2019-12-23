using PG.Control.Graphics;
using PG.Core.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Material
{
    public class MaterialEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public MaterialViewModel MaterialViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public MaterialEditViewModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.MaterialViewModel = new MaterialViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe( OnOk);
        }

        private void OnOk()
        {
            var world = MainModel.Instance.World;
            world.Scenes.UpdateMaterialScene(MaterialViewModel.Value, Name.Value, Id.Value );
            Canvas3d.Instance.Update(world);
            Canvas3d.Instance.Render();
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var id = (int)navigationContext.Parameters["Id"];
            var command = new PG.CLI.Command(PG.MaterialGetLabels.CommandNameLabel);
            command.SetArg(PG.MaterialGetLabels.IdLabel, id);
            command.Execute(MainModel.Instance.World.Adapter);
            var ambient = command.GetResult<ColorRGBA>(PG.MaterialGetLabels.AmbientLabel);
            var diffuse = command.GetResult<ColorRGBA>(PG.MaterialGetLabels.DiffuseLabel);
            var specular = command.GetResult<ColorRGBA>(PG.MaterialGetLabels.SpecularLabel);
            var shininess = command.GetResult<float>(PG.MaterialGetLabels.ShininessLabel);

            var material = new PG.Core.Graphics.Material();
            material.Ambient = ambient;
            material.Diffuse = diffuse;
            material.Specular = specular;
            material.Shininess = shininess;
            this.MaterialViewModel.Value = material;

            /*
            Id.Value = id;
            Name.Value = name;
            var ambient = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.AmbientLabel, id);
            var diffuse = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.DiffuseLabel, id);
            var specular = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.SpecularLabel, id);
//            var shininess = PG.CLI.Command.Get<float>(MainModel.Instance.World.Adapter, PG.GetLabels.Shininess)
           // var material = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindMaterialByid(item.Id);
           */
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }

    }
}
