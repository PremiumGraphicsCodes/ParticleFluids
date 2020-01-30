using PG.CGStudio.Object.Select;
using Reactive.Bindings;
using System.Windows.Forms;

namespace PG.CGStudio.Scene
{
    public class SceneExportViewModel
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }
            = new ShapeSelectViewModel();

        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>();

        public ReactiveCommand FileSelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        public SceneExportViewModel()
        {
            this.FileSelectCommand.Subscribe(OnFileSelect);
            this.ExportCommand.Subscribe(OnExport);
        }

        private void OnFileSelect()
        {
            var dialog = new SaveFileDialog()
            {
                Title = "Export",
                Filter = "STLFile(*.stl)|*.stl|OBJFile(*.obj)|*.obj|PCDFile(*.pcd)|*.pcd|すべてのファイル(*.*)|*.*",
            };
            if (DialogResult.OK == dialog.ShowDialog())
            {
                this.FilePath.Value = dialog.FileName;
            }
        }

        private void OnExport()
        {
            var world = World.Instance;
            var command = new PG.CLI.Command(PG.FileExportLabels.FileExportCommandLabel);
            command.SetArg(PG.FileExportLabels.IdLabel, ShapeSelectViewModel.Id.Value);
            command.SetArg(PG.FileExportLabels.FilePathLabel, FilePath.Value);
            command.Execute(world.Adapter);
            var isOk = command.GetResult<bool>(PG.FileExportLabels.IsOkLabel);
        }
    }
}
