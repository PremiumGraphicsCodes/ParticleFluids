using PG.Control.OpenGL;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.PolygonMesh
{
    public class FaceGroupEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public ReactiveProperty<string> MaterialName { get; }
            = new ReactiveProperty<string>();

        public ReactiveCommand ApplyCommand { get; }
            = new ReactiveCommand();

        private readonly World world;

        private readonly Canvas3d canvas;

        public FaceGroupEditViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            ApplyCommand.Subscribe(OnApply);
        }

        private void OnApply()
        {
            PG.CLI.Command.Set(world.Adapter, PG.SetLabels.NameLabel, Id.Value, Name.Value);
            PG.CLI.Command.Set(world.Adapter, PG.SetLabels.MaterialNameLabel, Id.Value, MaterialName.Value);
            canvas.Update(world);
            canvas.Render();
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
            ;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            /*
            var id = (int)navigationContext.Parameters["Id"];
            Id.Value = id;
            var name = PG.CLI.Command.Get<string>(World.Instance.Adapter, PG.GetLabels.NameLabel, id);
            Name.Value = name;
            var materialName = PG.CLI.Command.Get<string>(World.Instance.Adapter, PG.GetLabels.MaterialNameLabel, id);
            MaterialName.Value = materialName;
            */
        }

    }
}
