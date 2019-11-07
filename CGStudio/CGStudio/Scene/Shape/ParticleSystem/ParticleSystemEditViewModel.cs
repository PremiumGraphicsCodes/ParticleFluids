using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Scene.Shape.ParticleSystem
{
    public class ParticleSystemEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public ReactiveCommand EditCommand { get; }
            = new ReactiveCommand();

        public ParticleSystemEditViewModel()
        {
            EditCommand.Subscribe(OnEdit);
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
            var item = navigationContext.Parameters["ParticleSystemEdit"] as SceneModel;
            if (item == null)
            {
                return;
            }
            Id.Value = item.Id.Value;
            Name.Value = item.Name.Value;
        }

        private void OnEdit()
        {
            PG.CLI.Command.Set<string>(MainModel.Instance.World.Adapter, "Name", Id.Value, Name.Value);
            MainModel.Instance.World.Scenes.Sync();
            //Command.Set<string>(world, "Name", id, "AAA");

        }
    }
}
