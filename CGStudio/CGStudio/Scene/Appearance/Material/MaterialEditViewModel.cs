using PG.Control.Graphics;
using PG.Core;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Material
{
    public class MaterialEditViewModel : BindableBase, INavigationAware
    {
        public MaterialViewModel MaterialViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public MaterialEditViewModel()
        {
            this.MaterialViewModel = new MaterialViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe( OnOk);
        }

        private void OnOk()
        {

        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["MaterialEdit"] as Scene;
            if (item == null)
            {
                return;
            }
            var material = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindMaterialByid(item.Id);
            this.MaterialViewModel.Value = material;
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
