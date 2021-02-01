using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics.MeshBoundary
{
    public class MeshBoundarySceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Boundary01");

        public ReactiveCommand MeshFileSelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> MeshFilePath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        private MeshBoundaryScene scene;

        private SceneList world;

        private MainModel mainModel;

        private Canvas3d canvas;

        public MeshBoundarySceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.mainModel = model;
            this.canvas = canvas;
            this.MeshFileSelectCommand.Subscribe(OnSelectMeshFile);
            this.world = world;
            this.UpdateCommand.Subscribe(OnUpdate);
        }

        private void OnSelectMeshFile()
        {
            var dialog = new OpenFileDialog()
            {
                Title = "Import",
                Filter = "MeshFile(*.obj)|*.obj|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                this.MeshFilePath.Value = dialog.FileName;
                this.scene.SetMeshFromFile(world, mainModel.VDBModel, canvas, dialog.FileName);
            }
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as MeshBoundaryScene;
            if (item == null)
            {
                return;
            }
            this.Name.Value = item.Name;
            this.MeshFilePath.Value = item.MeshFilePath;
            this.scene = item;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        private void OnUpdate()
        {
            if (scene == null)
            {
                return;
            }
            //var sourceId = SourceParticleSystemSelectViewModel.Id.Value;
            //this.scene.Update(world, name, isBoundary);
        }
    }
}
