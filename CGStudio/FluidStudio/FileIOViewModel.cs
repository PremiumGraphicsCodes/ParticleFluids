using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Scene;
using Reactive.Bindings;
using System.Windows;
using Labels = PG.VDBFileReadLabels;

namespace FluidStudio
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

        private readonly SceneList world;

        private readonly Canvas3d canvas;

        public FileIOViewModel(SceneList world, Canvas3d canvas)
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
            /*
            world.Scenes.Clear();
            canvas.Renderer.Build(world.Adapter);
            canvas.Update();
            canvas.Render();
            */
        }

        private void OnOpen()
        {
            PG.CLI.PhysicsCommand command = new PG.CLI.PhysicsCommand();
            command.Create(PG.ParticleSystemCreateLabels.ParticleSystemAddLabel);
            command.Execute(world.Adapter);

            var dialog = new OpenFileDialog
            {
                Title = "Open",
                Filter = "FSProjectFile(*.fsproj)|*.fsproj|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                //world.Open(dialog.FileName);
            }
        }

        private void OnSave()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Save",
                Filter = "FSProjectFile(*.fsproj)|*.fsproj|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                //world.Save(dialog.FileName);
            }
        }

        private void OnSaveAs()
        {
            var dialog = new SaveFileDialog
            {
                Title = "SaveAs"
            };
            if (dialog.ShowDialog() == true)
            {
                //world.Save(dialog.FileName);
            }
        }

        private void OnImport()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Import",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                if (Import(dialog.FileName))
                {
                    world.Sync();
                    canvas.Update();
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
            /*
            var command = new PG.CLI.Command(PG.FileImportLabels.FileImportCommandLabel);
            command.SetArg(PG.FileImportLabels.FilePathLabel, filePath);
            command.Execute(world.Adapter);
            var isOk = command.GetResult<bool>(PG.FileImportLabels.IsOkLabel);
            return isOk;
            */
            var command = new PG.CLI.OpenVDBCommand(Labels.CommandNameLabel);
            command.SetArg(Labels.FilePathLabel, filePath);
            if (!command.Execute(world.Adapter))
            {
                return false;
            }
            var newId = command.GetResult<int>(Labels.NewIdLabel);
            return true;
        }

        private void OnExport()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true)
            {
                if (Export(dialog.FileName))
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