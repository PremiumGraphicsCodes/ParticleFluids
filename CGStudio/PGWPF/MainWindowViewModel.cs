using PG.CGStudio.Light;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio
{
    public class MainWindowViewModel : BindableBase
    {
        public MainWindowViewModel()
        {
            LightCommand = new ReactiveCommand();
            LightCommand.Subscribe(OnShowLight);
        }

        public ReactiveCommand LightCommand { get; }

        private void OnShowLight()
        {
            var dialog = new LightView();
            dialog.Show();
        }
    }
}
