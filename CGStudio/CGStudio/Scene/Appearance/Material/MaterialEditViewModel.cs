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
            world.Scenes.SetMaterialScene(MaterialViewModel.Value, Name.Value, Id.Value );
            Canvas3d.Instance.Update(world);
            Canvas3d.Instance.Render();
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var id = (int)navigationContext.Parameters["Id"];
            this.Id.Value = id;
            var material = MainModel.Instance.World.Scenes.GetMaterialScene(id);
            this.MaterialViewModel.Value = material;
            this.Name.Value = PG.CLI.Command.Get<string>(MainModel.Instance.World.Adapter, PG.GetLabels.NameLabel, id);
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
