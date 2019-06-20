using PG.CGStudio.Object.Select;
using PG.CGStudio.UICtrl;
using PG.Control.Math;
using PG.Core;
using Prism.Mvvm;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Selection
{
    public class SphereRegionSelectViewModel : BindableBase
    {
        public SelectViewModel SelectViewModel { get; }

        public Sphere3dViewModel SphereViewModel { get; }

        public ReactiveCommand PickCommand { get; }

        public SphereRegionSelectViewModel()
        {
            SelectViewModel = new SelectViewModel();
            SphereViewModel = new Sphere3dViewModel();
            PickCommand = new ReactiveCommand();
            PickCommand.Subscribe(OnPickUI);
        }

        private void OnPickUI()
        {
            var picker = new ObjectPickUICtrl(10);
            picker.Action = OnPicked;
            Canvas3d.Instance.UICtrl = picker;
        }

        private void OnPicked(ObjectId id)
        {
            //var obj = MainModel.Instance.Repository.Objects.FindObjectById(id.parentId);
            //id.childId;
 //           SphereViewModel.Value.Center =;
        }
    }
}
