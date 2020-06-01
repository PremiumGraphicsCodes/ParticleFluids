using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Core;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Object.Select
{
    public class ShapeSelectViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand PickCommand { get; }
            = new ReactiveCommand();

        public PickUICtrl Picker { get; }

        private readonly Canvas3d canvas;

        public ShapeSelectViewModel(SceneList world, Canvas3d canvas)
        {
            PickCommand.Subscribe(OnPickUI);
            Picker = new PickUICtrl(world, canvas, 10, Core.SceneType.AllScene);
            Picker.AddAction( OnPicked );
        }

        private void OnPickUI()
        {
            canvas.UICtrl = Picker;
        }

        private void OnPicked(ObjectId id)
        {
            this.Id.Value = id.parentId;
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
