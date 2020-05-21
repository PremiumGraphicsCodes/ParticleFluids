using PG.Control.OpenGL;
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

        private readonly World world;

        private readonly Canvas3d canvas;

        public FileIOViewModel(World world, Canvas3d canvas)
        {
            this.world = world;
            this.canvas = canvas;
            NewCommand.Subscribe(OnNew);
            OpenCommand.Subscribe(OnOpen);
            SaveCommand.Subscribe(OnSave);
            SaveAsCommand.Subscribe(OnSaveAs);
            ImportCommand.Subscribe(OnImport);
            ExportCommand.Subscribe(OnExport);
        }

        private void OnNew()
        {
            world.New();
            canvas.Renderer.Build(world.Adapter);
            canvas.Update(world);
            canvas.Render();
        }

        private void OnOpen()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Open"
            };
            if ( DialogResult.OK == dialog.ShowDialog() )
            {
                world.Open(dialog.FileName);
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
                world.Save(dialog.FileName);
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
                world.Save(dialog.FileName);
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
                    world.Scenes.Sync();
                    canvas.Update(world);
                    canvas.Render();
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
            var command = new PG.CLI.Command(PG.FileImportLabels.FileImportCommandLabel);
            command.SetArg(PG.FileImportLabels.FilePathLabel, filePath);
            command.Execute(world.Adapter);
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
            var command = new PG.CLI.Command("FileExport");
            command.SetArg("FilePath", filePath);
            command.Execute(world.Adapter);
            var isOk = command.GetResult<bool>("IsOk");
            return false;
        }


    }
}
