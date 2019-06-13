using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Object.Transform
{
    public class TransformViewModel : BindableBase, INavigationAware
    {
        public ReactiveCommand MoveCommand { get; }

        public ReactiveCommand ScaleCommand { get; }

        public ReactiveCommand RotateCommand { get; }

        public TransformViewModel()
        {
            MoveCommand = new ReactiveCommand();
            ScaleCommand = new ReactiveCommand();
            RotateCommand = new ReactiveCommand();
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {

        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {

        }
    }
}
