using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.PolygonMesh
{
    public class PolygonMeshEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        private readonly SceneListModel world;

        public PolygonMeshEditViewModel(SceneListModel world)
        {
            this.world = world;
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
            var id = (int)navigationContext.Parameters["Id"];
            Id.Value = id;
            var command = new PG.CLI.Command(PG.SceneGetLabels.CommandLabel);
            command.SetArg(PG.SceneGetLabels.IdLabel, id);
            command.Execute(world.Adapter);
            var name = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
            Name.Value = name;
            /*
            if (item == null)
            {
                return;
            }
            Id.Value = item.Id;
            Name.Value = item.Name;
            */
        }
    }
}
