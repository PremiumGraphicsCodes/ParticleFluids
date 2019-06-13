using PG.CGStudio.UICtrl;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Object.Select
{
    public class SelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveCommand PickCommand { get; }

        public SelectViewModel()
        {
            Id = new ReactiveProperty<int>();
            PickCommand = new ReactiveCommand();
        }

        private void OnPickUI()
        {
            var picker = new ObjectPickUICtrl(10);
            OpenGLPresenter.Instance.UICtrl = picker;
            picker.Action = OnPicked;
        }

        private void OnPicked(int id)
        {
            this.Id.Value = id;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            ;
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
