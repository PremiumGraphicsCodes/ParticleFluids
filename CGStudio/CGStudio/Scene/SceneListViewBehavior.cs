using PG.Core;
using Prism.Regions;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace PG.CGStudio.Object
{
    public class SceneListViewBehavior : Behavior<TreeView>
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
            if (treeView == null)
            {
                return;
            }
            var selectedItem = treeView.SelectedItem as Scene;
            if (selectedItem == null)
            {
                return;
            }
            switch(selectedItem.Type)
            {
                case SceneType.PointLight:
                    var parameters = new NavigationParameters
                    {
                        { "Object", selectedItem }
                    };
                    MainWindowViewModel.Instance.NavigateWithParam("LightEdit", parameters);
                    break;
                default:
                    break;
            }
            /*
            var parameters = new NavigationParameters
            {
                { "Object", selectedItem }
            };
            MainWindowViewModel.Instance.NavigateWithParam("Object", parameters);
            */

        }
    }
}
