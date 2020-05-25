using PG.CGStudio.Object.Select;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Windows.Forms;

namespace PG.CGStudio.Scene
{
    public class SceneExportViewModel
    {
        public ShapeSelectViewModel ShapeSelectViewModel { get; }

        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>();

        public ReactiveCommand FileSelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        private readonly World world;

        public SceneExportViewModel(World world)
        {
            this.world = world;
            this.ShapeSelectViewModel = new ShapeSelectViewModel(world);
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
            var command = new PG.CLI.Command(PG.FileExportLabels.FileExportCommandLabel);
            var ids = new List<int>
            {
                ShapeSelectViewModel.Id.Value
            };
            //command.SetArg(PG.FileExportLabels.IdsLabel, ids);
            command.SetArg(PG.FileExportLabels.FilePathLabel, FilePath.Value);
            var isOk = command.Execute(world.Adapter);
        }
    }
}
