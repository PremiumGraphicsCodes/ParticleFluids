using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Material
{
    public class MaterialEditViewModel : BindableBase, INavigationAware
    {
        private MaterialModel PrevMaterial;

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
            this.MaterialViewModel.Update( this.PrevMaterial.Material );
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Material"] as MaterialModel;
            if (item != null)
            {
                this.PrevMaterial = item;
                this.MaterialViewModel.Value = item.Material;
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
