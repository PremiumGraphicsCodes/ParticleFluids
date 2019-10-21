using PG.Control.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Light
{
    public class LightEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public PointLightViewModel PointLightViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public LightEditViewModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.PointLightViewModel = new PointLightViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            var repository = MainModel.Instance.World;
//            repository.UpdateLightScene(Id.Value, PointLightViewModel.Value);
            Canvas3d.Instance.Update(repository);
            Canvas3d.Instance.Render();
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {

        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["LightEdit"] as PG.Core.Scene;
            if (item == null)
            {
                return;
            }
            this.Id.Value = item.Id;
            this.Name.Value = item.Name;
//            var light = MainModel.Instance.Repository.Adapter.GetSceneAdapter().FindLightById( item.Id );
//            this.PointLightViewModel.Value = light;
        }
    }
}
