﻿using Reactive.Bindings;
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

        public ReactiveProperty<bool> DoConvertToVolume { get; }
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
                this.DoConvertToVolume.Value = value.DoConvertToVolume;
            }
        }

        public FluidFileExportViewModel()
        {
            this.VDBExportDirectorySelectCommand.Subscribe(() => OnSelectVDBExportDirectory());
            this.DoExportVDB.Subscribe(OnExportVDBChanged);
            this.VDBExportDirectoryPath.Subscribe(OnExportVDBDirectoryChanged);
            this.DoConvertToVolume.Subscribe(OnConvertToVolumeChanged);
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

        private void OnConvertToVolumeChanged(bool b)
        {
            if (model != null)
            {
                model.DoConvertToVolume = b;
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