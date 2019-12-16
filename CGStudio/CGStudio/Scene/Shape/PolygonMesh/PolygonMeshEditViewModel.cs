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

        public PolygonMeshEditViewModel()
        {
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
            var name = PG.CLI.Command.Get<string>(MainModel.Instance.World.Adapter, PG.GetLabels.NameLabel, id);
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
