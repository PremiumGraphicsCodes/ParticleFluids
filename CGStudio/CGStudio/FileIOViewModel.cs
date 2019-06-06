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
            MainModel.Instance.Repository.New();
            OpenGLPresenter.Instance.Update(MainModel.Instance.Repository);
            OpenGLPresenter.Instance.Render();
        }

        private void OnOpen()
        {
            var dialog = new OpenFileDialog
            {
                Title = "Open"
            };
            if ( DialogResult.OK == dialog.ShowDialog() )
            {
                var model = MainModel.Instance.Repository;
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
                var model = MainModel.Instance.Repository;
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
                var model = MainModel.Instance.Repository;
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
                var model = MainModel.Instance.Repository;
                if(model.Import(dialog.FileName))
                {
                    model.Objects.Sync();
                    model.Material.Sync();
                    OpenGLPresenter.Instance.Update(MainModel.Instance.Repository);
                    OpenGLPresenter.Instance.Render();
                    MessageBox.Show("Import Suceeded");                    
                }
                else
                {
                    MessageBox.Show("Import Failed");
                }
            }
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
                var model = MainModel.Instance.Repository;
                if(model.Export(dialog.FileName))
                {
                    MessageBox.Show("Export Suceeded");
                }
                else
                {
                    MessageBox.Show("Export Failed");
                }
            }

        }

    }
}
