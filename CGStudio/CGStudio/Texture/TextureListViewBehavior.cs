using Prism.Regions;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace PG.CGStudio.Texture
{
    public class TextureListViewBehavior : Behavior<TreeView>
    {
        protected override void OnAttached()
        {
            this.AssociatedObject.MouseDoubleClick += this.ItemDoubleClicked;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.MouseDoubleClick -= this.ItemDoubleClicked;
        }

        private void ItemDoubleClicked(object sender, MouseButtonEventArgs e)
        {
            var treeView = e.Source as TreeView;
            if (treeView == null) return;
            var selectedItem = treeView.SelectedItem as PG.Core.Graphics.Texture;
            if (selectedItem == null) return;
            var parameters = new NavigationParameters();
            parameters.Add("Texture", selectedItem);
            MainWindowViewModel.Instance.NavigateWithParam("Texture", parameters);
        }
    }
}
