using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FluidStudio.Physics.Fluid
{
    public class FluidFileExportViewModel
    {
        public ReactiveCommand VDBExportDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand OBJExportDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> VDBExportDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<string> OBJExportDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<bool> DoExportVDB { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveProperty<bool> DoMakeMesh { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveProperty<bool> DoExportOBJ { get; }
            = new ReactiveProperty<bool>(false);

        public ReactiveProperty<double> Radius { get; }
            = new ReactiveProperty<double>(5.0);

        private FluidFileExportModel model;

        public FluidFileExportModel Model
        {
            set
            {
                this.model = value;
                this.DoExportVDB.Value = value.DoExportVDB;
                this.VDBExportDirectoryPath.Value = value.VDBExportDirectory;
                this.DoExportOBJ.Value = value.DoExportOBJ;
                this.OBJExportDirectoryPath.Value = value.OBJExportDirectory;
            }
        }

        public FluidFileExportViewModel()
        {
            this.VDBExportDirectorySelectCommand.Subscribe(() => OnSelectVDBExportDirectory());
            this.OBJExportDirectorySelectCommand.Subscribe(() => OnSelectOBJExportDirectory());
            this.DoExportVDB.Subscribe(OnExportVDBChanged);
            this.VDBExportDirectoryPath.Subscribe(OnExportVDBDirectoryChanged);
            this.OBJExportDirectoryPath.Subscribe(OnExportOBJDirectoryChanged);
            this.DoMakeMesh.Subscribe(OnMakeMeshChanged);
            this.DoExportOBJ.Subscribe(OnExportOBJChanged);
            this.Radius.Subscribe(OnRadiusChanged);
        }

        private void OnSelectVDBExportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.VDBExportDirectoryPath.Value = dialog.FileName;
            }
        }

        private void OnSelectOBJExportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.OBJExportDirectoryPath.Value = dialog.FileName;
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

        private void OnExportOBJDirectoryChanged(string path)
        {
            if (model != null)
            {
                model.OBJExportDirectory = path;
            }
        }

        private void OnMakeMeshChanged(bool b)
        {
            if (model != null)
            {
                model.DoMakeMesh = b;
            }
        }

        private void OnExportOBJChanged(bool b)
        {
            if (model != null)
            {
                model.DoExportOBJ = b;
            }
        }

        private void OnRadiusChanged(double r)
        {
            if(model != null)
            {
                model.Radius = r;
            }
        }

    }
}
