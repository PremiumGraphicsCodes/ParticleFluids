using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Regions;
using Reactive.Bindings;

namespace FluidStudio.Physics.Fluid
{
    class EmitterSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Fluid01");

        public ReactiveCommand ParticleFileSelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> ParticleFilePath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<float> ParticleRadius { get; }
            = new ReactiveProperty<float>(0.5f);

        public ReactiveProperty<float> Density { get; }
            = new ReactiveProperty<float>(1000.0f);

        public ReactiveProperty<float> Stiffness { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Viscosity { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<int> StartTimeStep { get; }
            = new ReactiveProperty<int>(0);

        public ReactiveProperty<int> EndTimeStep { get; }
            = new ReactiveProperty<int>(100);

        public ReactiveProperty<int> Interval { get; }
            = new ReactiveProperty<int>(10);

        public FluidFileExportViewModel ExportViewModel { get; }

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<bool> DoUseRelativePath { get; }
            = new ReactiveProperty<bool>(false);

        private EmitterScene scene;

        private readonly SceneList world;

        private readonly MainModel mainModel;

        private readonly Canvas3d canvas;

        public EmitterSceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.ExportViewModel = new FluidFileExportViewModel(model.FileIOModel);
            this.mainModel = model;
            this.canvas = canvas;
            this.ParticleFileSelectCommand.Subscribe(OnSelectPSFile);
            this.world = world;
            this.UpdateCommand.Subscribe(OnUpdate);
        }

        private void OnSelectPSFile()
        {
            var dialog = new OpenFileDialog()
            {
                Title = "Import",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                var filename = dialog.FileName;
                if (DoUseRelativePath.Value)
                {
                    filename = mainModel.FileIOModel.ToRelativePath(filename);
                }
                this.ParticleFilePath.Value = filename;
                this.scene.SetParticlesFromFile(mainModel.VDBModel, mainModel.FileIOModel, canvas, dialog.FileName, ParticleRadius.Value);
                this.OnUpdate();

                canvas.BuildShader(world, scene.Id);
                canvas.Render();

                canvas.Camera.Fit();
                canvas.Render();
            }
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as EmitterScene;
            if (item == null)
            {
                return;
            }
            //this.Id.Value = item.Id;
            this.Name.Value = item.Name;
            this.ParticleFilePath.Value = item.ParticleFilePath;
            this.ParticleRadius.Value = item.ParticleRadius;
            this.Density.Value = item.Density;
            this.Stiffness.Value = item.Stiffness;
            this.Viscosity.Value = item.Viscosity;
            this.StartTimeStep.Value = item.StartTimeStep;
            this.EndTimeStep.Value = item.EndTimeStep;
            this.Interval.Value = item.Interval;
            //this.IsBoundary.Value = item.IsBoundary;
            this.ExportViewModel.Model = item.ExportModel;
//            this.
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

            this.scene.ParticleRadius = ParticleRadius.Value;
            this.scene.Density = Density.Value;
            this.scene.Stiffness = Stiffness.Value;
            this.scene.Viscosity = Viscosity.Value;
            this.scene.Name = Name.Value;
            this.scene.StartTimeStep = StartTimeStep.Value;
            this.scene.EndTimeStep = EndTimeStep.Value;
            this.scene.Interval = Interval.Value;
            this.scene.Send();
        }

    }
}
