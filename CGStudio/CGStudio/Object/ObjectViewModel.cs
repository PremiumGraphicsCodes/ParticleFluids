using PG.Control.Shape;
using Prism.Mvvm;
using Prism.Regions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Object
{
    public class ObjectViewModel : BindableBase, INavigationAware
    {
        public PolygonMeshViewModel PolygonMeshViewModel { get; }

        public ObjectViewModel()
        {
            this.PolygonMeshViewModel = new PolygonMeshViewModel();
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Object"] as ObjectModel;
            if (item != null)
            {
//                this.PrevMaterial = item.Material;
//                this.MaterialViewModel.Value = item.Material;
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
