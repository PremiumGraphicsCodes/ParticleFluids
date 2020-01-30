using Reactive.Bindings;
using System.Windows.Forms;

namespace PG.CGStudio
{
    public class FileIOViewModel
    {
        public ReactiveCommand NewCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OpenCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand SaveCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand SaveAsCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ImportCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand ExportCommand { get; }
            = new ReactiveCommand();

        public FileIOViewModel()
        {
            NewCommand.Subscribe(OnNew);
            OpenCommand.Subscribe(OnOpen);
            SaveCommand.Subscribe(OnSave);
            SaveAsCommand.Subscribe(OnSaveAs);
            ImportCommand.Subscribe(OnImport);
            ExportCommand.Subscribe(OnExport);
        }

        private void OnNew()
        {
            MainModel.Instance.World.New();
            World.Instance.Renderer.Build(MainModel.Instance.World.Adapter);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }

        private void OnOpen()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Open"
            };
            if ( DialogResult.OK == dialog.ShowDialog() )
            {
                var model = MainModel.Instance.World;
                model.Open(dialog.FileName);
            }
        }

        private void OnSave()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Save"
            };
            if ( DialogResult.OK == dialog.ShowDialog() )
            {
                var model = MainModel.Instance.World;
                model.Save(dialog.FileName);
            }
        }

        private void OnSaveAs()
        {
            var dialog = new SaveFileDialog
            {
                Title = "SaveAs"
            };
            if (DialogResult.OK == dialog.ShowDialog())
            {
                var model = MainModel.Instance.World;
                model.Save(dialog.FileName);
            }
        }

        private void OnImport()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Import",
                Filter = "STLFile(*.stl)|*.stl|OBJFile(*.obj)|*.obj|PCDFile(*.pcd)|*.pcd|すべてのファイル(*.*)|*.*",
            };
            if (DialogResult.OK == dialog.ShowDialog())
            {
                if(Import(dialog.FileName))
                {
                    MainModel.Instance.World.Scenes.Sync();
                    Canvas3d.Instance.Update(MainModel.Instance.World);
                    Canvas3d.Instance.Render();
                    MessageBox.Show("Import Suceeded");                    
                }
                else
                {
                    MessageBox.Show("Import Failed");
                }
            }
        }

        private bool Import(string filePath)
        {
            var model = MainModel.Instance.World;
            var command = new PG.CLI.Command(PG.FileImportLabels.FileImportCommandLabel);
            command.SetArg(PG.FileImportLabels.FilePathLabel, filePath);
            command.Execute(model.Adapter);
            var isOk = command.GetResult<bool>(PG.FileImportLabels.IsOkLabel);
            return isOk;
        }

        private void OnExport()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "STLFile(*.stl)|*.stl|OBJFile(*.obj)|*.obj|PCDFile(*.pcd)|*.pcd|すべてのファイル(*.*)|*.*",
            };
            if (DialogResult.OK == dialog.ShowDialog())
            {
                if(Export(dialog.FileName))
                {
                    MessageBox.Show("Export Suceeded");
                }
                else
                {
                    MessageBox.Show("Export Failed");
                }
            }
        }

        private bool Export(string filePath)
        {
            var model = MainModel.Instance.World;
            var command = new PG.CLI.Command("FileExport");
            command.SetArg("FilePath", filePath);
            command.Execute(model.Adapter);
            var isOk = command.GetResult<bool>("IsOk");
            return false;
        }


    }
}
