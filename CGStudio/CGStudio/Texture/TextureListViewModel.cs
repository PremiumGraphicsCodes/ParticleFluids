using System.Collections.ObjectModel;

namespace PG.CGStudio.Texture
{
    public class TextureListViewModel
    {
        public ObservableCollection<PG.Core.Graphics.Texture> Items { get; set; }

        public TextureListViewModel()
        {
            Items = new ObservableCollection<PG.Core.Graphics.Texture>();
            var item1 = new PG.Core.Graphics.Texture();
            item1.Name.Value = "Texture1";
            item1.IsVisible.Value = true;
            var item2 = new PG.Core.Graphics.Texture();
            item2.Name.Value = "Texture2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
        }
    }
}
