using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using Prism.Regions;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Scene.Shape.Transform
{
    public class TranslateViewModel : INavigationAware
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public Vector3dViewModel VectorViewModel { get; }
            = new Vector3dViewModel();

        public ReactiveCommand TranslateCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public TranslateViewModel()
        {
            this.TranslateCommand.Subscribe(OnTranslate);
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
        }

        private void OnTranslate()
        {
            var ids = new List<int>
            {
                ShapeSelectViewModel.Id.Value
            };
            var moveCtrl = new TranslateUICtrl(ids);
            Canvas3d.Instance.UICtrl = moveCtrl;
        }
    }
}
