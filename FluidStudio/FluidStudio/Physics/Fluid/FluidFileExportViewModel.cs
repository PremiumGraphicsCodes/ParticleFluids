using Reactive.Bindings;
using System;

namespace FluidStudio.Physics.Fluid
{
    public class FluidFileExportViewModel
    {
        public ReactiveCommand VDBExportDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> VDBExportDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<bool> DoExportVDB { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveProperty<bool> DoUseRelativePath { get; }
            = new ReactiveProperty<bool>(false);

        private FluidFileExportModel model;

        private FileIOModel ioModel;

        public FluidFileExportModel Model
        {
            set
            {
                this.model = value;
                this.DoExportVDB.Value = value.DoExportVDB;
                this.VDBExportDirectoryPath.Value = value.VDBExportDirectory;
            }
        }

        public FluidFileExportViewModel(FileIOModel ioModel)
        {
            this.ioModel = ioModel;
            this.VDBExportDirectorySelectCommand.Subscribe(() => OnSelectVDBExportDirectory());
            this.DoExportVDB.Subscribe(OnExportVDBChanged);
            this.VDBExportDirectoryPath.Subscribe(OnExportVDBDirectoryChanged);
        }

        private void OnSelectVDBExportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                var dirname = dialog.FileName;
                if(DoUseRelativePath.Value)
                {
                    dirname = ioModel.ToRelativePath(dirname);
                }
                this.VDBExportDirectoryPath.Value = dirname;
            }
        }

        private void OnExportVDBChanged(bool b)
        {
            if (model != null)
            {
                model.DoExportVDB = b;
            }
        }

        private void OnExportVDBDirectoryChanged(string path)
        {
            if (model != null)
            {
                model.VDBExportDirectory = path;
            }
        }
    }
}
