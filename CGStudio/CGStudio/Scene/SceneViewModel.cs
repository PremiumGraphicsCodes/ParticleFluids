using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Object
{
    public class SceneViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public SceneViewModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
 //           this.PolygonMeshViewModel = new PolygonMeshViewModel();

        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Object"] as SceneModel;
            if (item != null)
            {
                Id.Value = item.Id.Value;
                Name.Value = item.Name.Value;
//                this.PrevMaterial = item.Material;
//                this.MaterialViewModel.Value = item.Material;
            }

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
