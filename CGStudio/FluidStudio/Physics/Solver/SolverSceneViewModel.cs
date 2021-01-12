using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Windows.Forms;

namespace FluidStudio.Physics.Solver
{
    public class SolverSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Solver01");

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<float> TimeStep { get; }
            = new ReactiveProperty<float>(0.03f);

        private SolverScene scene;

        private readonly SceneList world;

        public ReactiveCommand VDBExportDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OBJExportDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> VDBExportDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<string> OBJExportDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<bool> DoExportVDB { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveProperty<bool> DoMakeMesh { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveProperty<bool> DoExportOBJ { get; }
            = new ReactiveProperty<bool>(false);

        public SolverSceneViewModel(SceneList world)
        {
            this.world = world;
            this.UpdateCommand.Subscribe(OnUpdate);
            this.VDBExportDirectorySelectCommand.Subscribe(() => OnSelectVDBExportDirectory());
            this.OBJExportDirectorySelectCommand.Subscribe(() => OnSelectOBJExportDirectory());
            this.DoExportVDB.Subscribe(OnExportVDBChanged);
            this.VDBExportDirectoryPath.Subscribe(OnExportVDBDirectoryChanged);
            this.OBJExportDirectoryPath.Subscribe(OnExportOBJDirectoryChanged);
            this.DoMakeMesh.Subscribe(OnMakeMeshChanged);
            this.DoExportOBJ.Subscribe(OnExportOBJChanged);
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
            var item = navigationContext.Parameters["Scene"] as SolverScene;
            if (item == null)
            {
                return;
            }
            this.Name.Value = item.Name;
            this.Id.Value = Id.Value;
            this.scene = item;
        }

        private void OnUpdate()
        {
            scene.Update(world, this.scene.Fluids, this.scene.CSGBoundaries, TimeStep.Value, this.Name.Value);
        }

        private void OnSelectVDBExportDirectory()
        {
            var dialog = new FolderBrowserDialog();
            var result = dialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                this.VDBExportDirectoryPath.Value = dialog.SelectedPath;
            }
        }

        private void OnSelectOBJExportDirectory()
        {
            var dialog = new FolderBrowserDialog();
            var result = dialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                this.OBJExportDirectoryPath.Value = dialog.SelectedPath;
            }
        }

        private void OnExportVDBChanged(bool b)
        {
            if (scene != null)
            {
                scene.DoExportVDB = b;
            }
        }

        private void OnExportVDBDirectoryChanged(string path)
        {
            if (scene != null)
            {
                scene.VDBExportDirectory = path;
            }
        }

        private void OnExportOBJDirectoryChanged(string path)
        {
            if (scene != null)
            {
                scene.OBJExportDirectory = path;
            }
        }

        private void OnMakeMeshChanged(bool b)
        {
            if (scene != null)
            {
                scene.DoMakeMesh = b;
            }
        }

        private void OnExportOBJChanged(bool b)
        {
            if(scene != null)
            {
                scene.DoExportOBJ = b;
            }
        }
    }
}
