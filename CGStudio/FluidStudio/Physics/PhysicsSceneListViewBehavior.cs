using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

using Prism.Regions;

using PG.Core;

namespace FluidStudio.Physics
{
    public class PhysicsSceneListViewBehavior : Behavior<TreeView>
    {
        /*
        protected override void OnAttached()
        {
            this.AssociatedObject.MouseDoubleClick += this.ItemDoubleClicked;
            this.AssociatedObject.KeyDown += this.KeyDowned;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.MouseDoubleClick -= this.ItemDoubleClicked;
            this.AssociatedObject.KeyDown -= this.KeyDowned;
        }

        private void KeyDowned(object sender, KeyEventArgs e)
        {
            var treeView = e.Source as TreeView;
            if (treeView == null)
            {
                return;
            }
            var selectedItem = treeView.SelectedItem as SceneModel;
            if (selectedItem == null)
            {
                return;
            }
        }

        private void ItemDoubleClicked(object sender, MouseButtonEventArgs e)
        {
            var view = sender as TreeView;
            var treeView = e.Source as TreeView;
            if (treeView == null)
            {
                return;
            }
            var viewModel = treeView.DataContext as SceneListViewModel;
            var selectedItem = treeView.SelectedItem as SceneModel;

            viewModel.ChangeView(selectedItem);
        }
        */
    }
}
