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
            var selectedItem = treeView.SelectedItem as TextureItem;
            if (selectedItem == null) return;
            MainWindowViewModel.Instance.NavigateCommand.Execute("Texture");
        }
    }
}
