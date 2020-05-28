using PG.Control.Graphics;
using PG.Control.OpenGL;
using PG.Core.Graphics;
using PG.Scene;
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

        private readonly SceneListModel world;

        private readonly Canvas3d canvas;

        public MaterialEditViewModel(SceneListModel world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.MaterialViewModel = new MaterialViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe( OnOk);
        }

        private void OnOk()
        {
            world.SetMaterialScene(MaterialViewModel.Value, Name.Value, Id.Value );
            canvas.Update();
            canvas.Render();
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var id = (int)navigationContext.Parameters["Id"];
            this.Id.Value = id;
            var material = world.GetMaterialScene(id);
            this.MaterialViewModel.Value = material;
            var command = new PG.CLI.Command();
            command.SetArg(PG.SceneGetLabels.IdLabel, id);
            command.Execute(world.Adapter);
            this.Name.Value = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
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
