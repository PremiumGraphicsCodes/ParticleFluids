﻿using PG.Control.Graphics;
using PG.Core.Graphics;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;

namespace PG.CGStudio.Material
{
    public class MaterialEditViewModel : BindableBase, INavigationAware
    {
        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public MaterialViewModel MaterialViewModel { get; }

        public ReactiveCommand OKCommand { get; }

        public MaterialEditViewModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.MaterialViewModel = new MaterialViewModel();
            this.OKCommand = new ReactiveCommand();
            this.OKCommand.Subscribe( OnOk);
        }

        private void OnOk()
        {
            var world = World.Instance;
            world.Scenes.SetMaterialScene(MaterialViewModel.Value, Name.Value, Id.Value );
            HwndHostPresenter3d.Instance.Update(world);
            HwndHostPresenter3d.Instance.Render();
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var id = (int)navigationContext.Parameters["Id"];
            this.Id.Value = id;
            var material = World.Instance.Scenes.GetMaterialScene(id);
            this.MaterialViewModel.Value = material;
            var command = new PG.CLI.Command();
            command.SetArg(PG.SceneGetLabels.IdLabel, id);
            command.Execute(World.Instance.Adapter);
            this.Name.Value = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
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
