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
            Repository.Instance.New();
        }

        private void OnOpen()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Open"
            };
            if ( DialogResult.OK == dialog.ShowDialog() )
            {
                var model = Repository.Instance;
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
                var model = Repository.Instance;
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
                var model = Repository.Instance;
                model.Save(dialog.FileName);
            }
        }

        private void OnImport()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Import"
            };
            if (DialogResult.OK == dialog.ShowDialog())
            {
                var model = Repository.Instance;
                model.Import(dialog.FileName);
            }
        }

        private void OnExport()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export"
            };
            if (DialogResult.OK == dialog.ShowDialog())
            {
                var model = Repository.Instance;
                model.Export(dialog.FileName);
            }

        }

    }
}
