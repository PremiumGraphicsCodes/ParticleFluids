using PG.CLI;
using PG.Control.OpenGL;
using PG.Scene;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FluidStudio
{
    public class TimeLineViewModel : BindableBase
    {
        public ReactiveProperty<int> TimeStep { get; }

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand StopCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ResetCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OutputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> OutputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<bool> DoOutput { get; }
            = new ReactiveProperty<bool>(false);

        private readonly MainModel mainModel;

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        private bool isStop = false;

        public TimeLineViewModel(MainModel mainModel, SceneList scenes, Canvas3d canvas)
        {
            this.mainModel = mainModel;
            this.scenes = scenes;
            this.canvas = canvas;
            this.TimeStep = mainModel.PhysicsModel.TimeStep;
            StartCommand.Subscribe(() => OnStart());
            StopCommand.Subscribe(() => OnStop());
            ResetCommand.Subscribe(() => OnReset());
            OutputDirectorySelectCommand.Subscribe(() => OnSelectOutputDirectory());
        }

        private void OnStart()
        {
            isStop = false;
            Task.Run(() => Simulate());
        }

        private void OnStop()
        {
            isStop = true;
        }

        private void Simulate()
        {
            var vdb = mainModel.VDBModel;
            while(!isStop)
            {
                mainModel.PhysicsModel.Simulate(scenes, canvas);
                mainModel.PhysicsModel.ConvertToMesh(scenes, vdb, canvas);
                var filePath = OutputDirectoryPath.Value + "/" + "Shape" + "_" + TimeStep.Value.ToString() + ".obj";
                mainModel.Scenes.Export(filePath);
                if (DoOutput.Value)
                {
                    mainModel.PhysicsModel.ExportVDB(scenes, vdb, OutputDirectoryPath.Value);
                }
            }
        }

        private void OnReset()
        {
            mainModel.PhysicsModel.Reset(scenes, canvas);
            //mainModel.PhysicsModel.Reset();
        }

        private void OnSelectOutputDirectory()
        {
            var dialog = new FolderBrowserDialog();
            var result = dialog.ShowDialog();
            if(result == DialogResult.OK)
            {
                this.OutputDirectoryPath.Value = dialog.SelectedPath;
            }
        }
    }
}
