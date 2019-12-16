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

        public ReactiveCommand ApplyCommand { get; }
            = new ReactiveCommand();

        public FaceGroupEditViewModel()
        {
            ApplyCommand.Subscribe(OnApply);
        }

        private void OnApply()
        {
            PG.CLI.Command.Set(MainModel.Instance.World.Adapter, PG.SetLabels.NameLabel, Id.Value, Name.Value);
            PG.CLI.Command.Set(MainModel.Instance.World.Adapter, PG.SetLabels.MaterialNameLabel, Id.Value, MaterialName.Value);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
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
            var id = (int)navigationContext.Parameters["Id"];
            Id.Value = id;
            var name = PG.CLI.Command.Get<string>(MainModel.Instance.World.Adapter, PG.GetLabels.NameLabel, id);
            Name.Value = name;
            var materialName = PG.CLI.Command.Get<string>(MainModel.Instance.World.Adapter, PG.GetLabels.MaterialNameLabel, id);
            MaterialName.Value = materialName;
        }

    }
}
