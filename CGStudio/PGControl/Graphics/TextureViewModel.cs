using Prism.Mvvm;
using Reactive.Bindings;
using System.Windows.Forms;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using static System.Net.Mime.MediaTypeNames;

namespace PG.Control.Graphics
{
    public class TextureViewModel : BindableBase
    {
        public ReactiveProperty<string> ImagePath { get; }

        public ReactiveCommand FileSelectCommand { get; }

        public TextureViewModel()
        {
            ImagePath = new ReactiveProperty<string>();
            FileSelectCommand = new ReactiveCommand();
            FileSelectCommand.Subscribe(OnFileSelect);
        }

        private void OnFileSelect()
        {
            OpenFileDialog dialog = new OpenFileDialog();
            if(DialogResult.OK == dialog.ShowDialog() )
            {
                ImagePath.Value = dialog.FileName;
            }
        }
    }
}
