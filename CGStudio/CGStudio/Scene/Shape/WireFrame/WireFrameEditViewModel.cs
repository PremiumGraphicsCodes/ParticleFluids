using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using PG.Scene;

namespace PG.CGStudio.Scene.Shape.WireFrame
{
    public class WireFrameEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public ReactiveCommand EditCommand { get; }
            = new ReactiveCommand();

        private readonly World world;

        public WireFrameEditViewModel(World world)
        {
            this.world = world;
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
            var item = navigationContext.Parameters["WireFrameEdit"] as SceneModel;
            if (item == null)
            {
                return;
            }
            Id.Value = item.Id.Value;
            Name.Value = item.Name.Value;
        }

        private void OnEdit()
        {
            PG.CLI.Command.Set<string>(world.Adapter, "Name", Id.Value, Name.Value);
            world.Scenes.Sync();
        }
    }
}
