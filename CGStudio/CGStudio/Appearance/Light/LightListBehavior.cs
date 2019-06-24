using PG.Core.Graphics;
using Prism.Regions;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace PG.CGStudio.Light
{
    public class LightListViewBehavior : Behavior<TreeView>
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
            var selectedItem = treeView.SelectedItem as PointLight;
            if (selectedItem == null) return;
            var parameters = new NavigationParameters();
            parameters.Add("Light", selectedItem);
            MainWindowViewModel.Instance.NavigateWithParam("Light", parameters);
        }
    }
}
