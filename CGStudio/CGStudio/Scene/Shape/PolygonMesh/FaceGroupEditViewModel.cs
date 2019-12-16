using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Scene.Shape.PolygonMesh
{
    public class FaceGroupEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>();

        public ReactiveProperty<string> MaterialName { get; }
            = new ReactiveProperty<string>();

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
            var item = navigationContext.Parameters["FaceGroupEdit"] as PG.Core.Scene;
            if (item == null)
            {
                return;
            }
            Id.Value = item.Id;
            Name.Value = item.Name;
        }

    }
}
