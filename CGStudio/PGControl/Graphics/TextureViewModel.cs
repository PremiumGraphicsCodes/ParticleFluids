using PG.Core.Graphics;
using Prism.Mvvm;
using Reactive.Bindings;
using System.Windows.Forms;

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

        public Texture Value
        {
            set
            {
                ImagePath.Value = value.ImagePath;
            }
        }

        public void Update(Texture texture)
        {
            texture.ImagePath = ImagePath.Value;
        }
    }
}
