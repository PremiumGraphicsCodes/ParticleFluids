using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.PolygonMesh
{
    public class PolygonMeshEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public PolygonMeshEditViewModel()
        {
            Id = new ReactiveProperty<int>();
            Name = new ReactiveProperty<string>();
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
            var item = navigationContext.Parameters["PolygonMeshEdit"] as PG.Core.Scene;
            if (item == null)
            {
                return;
            }
            Id.Value = item.Id;
            Name.Value = item.Name;
        }
    }
}
