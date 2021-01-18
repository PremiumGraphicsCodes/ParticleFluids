using Microsoft.Win32;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Reactive.Bindings;

namespace FluidStudio.FileIO
{
    public class ExportViewModel
    {
        public SceneSelectViewModel SceneSelectViewModel { get; }

        public ReactiveProperty<string> FilePath { get; }
            = new ReactiveProperty<string>("");

        public ReactiveCommand SelectCommand { get; }
            = new ReactiveCommand();

        public ExportViewModel(SceneList scenes, Canvas3d canvas)
        {
            SceneSelectViewModel = new SceneSelectViewModel(scenes, canvas);
            SelectCommand.Subscribe(OnSelect);
        }

        private void OnSelect()
        {
            var dialog = new SaveFileDialog
            {
                Title = "Export",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            var isOk = dialog.ShowDialog();
            if(isOk == true)
            {
                this.FilePath.Value = dialog.FileName;
            }
        }
    }
}
