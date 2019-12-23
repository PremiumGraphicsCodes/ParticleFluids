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
            var name = PG.CLI.Command.Get<string>(MainModel.Instance.World.Adapter, PG.GetLabels.NameLabel, id);
            Id.Value = id;
            Name.Value = name;
            var ambient = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.AmbientLabel, id);
            var diffuse = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.DiffuseLabel, id);
            var specular = PG.CLI.Command.Get<ColorRGBA>(MainModel.Instance.World.Adapter, PG.GetLabels.SpecularLabel, id);
//            var shininess = PG.CLI.Command.Get<float>(MainModel.Instance.World.Adapter, PG.GetLabels.Shininess)
           // var material = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindMaterialByid(item.Id);
           // this.MaterialViewModel.Value = material;
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
