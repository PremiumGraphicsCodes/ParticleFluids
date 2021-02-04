using Reactive.Bindings;

namespace FluidStudio.Tool.Modeling
{
    public class PSToVolumeViewModel
    {
        public ReactiveCommand VDBInputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveCommand VDBOutputDirectorySelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> VDBInputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveProperty<string> VDBOutputDirectoryPath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand StartCommand { get; }
            = new ReactiveCommand();

        public PSToVolumeViewModel()
        {
            this.VDBInputDirectorySelectCommand.Subscribe(OnSelectVDBImportDirectory);
            this.VDBOutputDirectorySelectCommand.Subscribe(OnSelectVDBExportDirectory);
            this.StartCommand.Subscribe(OnStart);
        }

        private void OnSelectVDBImportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.VDBInputDirectoryPath.Value = dialog.FileName;
            }
        }

        private void OnSelectVDBExportDirectory()
        {
            var dialog = new Microsoft.WindowsAPICodePack.Dialogs.CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            var result = dialog.ShowDialog();
            if (result == Microsoft.WindowsAPICodePack.Dialogs.CommonFileDialogResult.Ok)
            {
                this.VDBOutputDirectoryPath.Value = dialog.FileName;
            }
        }

        private void OnStart()
        {
            // vdbファイルを列挙する．
            // 一つ一つコンバートしてexportDirectoryに保存する．
        }
    }
}
