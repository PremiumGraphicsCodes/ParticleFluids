using PG.Control.Graphics;
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
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
//            MainModel.Instance.Repository.Material.
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Material"] as PG.Core.Graphics.Material;
            if (item != null)
            {
                this.MaterialViewModel.Value = item;
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
