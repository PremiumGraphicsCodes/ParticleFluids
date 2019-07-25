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
            var selectedItem = treeView.SelectedItem as PG.Core.Scene;
            if (selectedItem == null)
            {
                return;
            }
            var parameters = new NavigationParameters();
            switch(selectedItem.Type)
            {
                case SceneType.ParticleSystem:
                    parameters.Add("ParticleSystemEdit", selectedItem);
                    MainWindowViewModel.Instance.NavigateWithParam("ParticleSystemEdit", parameters);
                    break;
                case SceneType.WireFrame:
                    parameters.Add("WireFrameEdit", selectedItem);
                    MainWindowViewModel.Instance.NavigateWithParam("WireFrameEdit", parameters);
                    break;
                case SceneType.PolygonMesh:
                    parameters.Add("PolygonMeshEdit", selectedItem);
                    MainWindowViewModel.Instance.NavigateWithParam("PolygonMeshEdit", parameters);
                    break;
                case SceneType.PointLight:
                    parameters.Add("LightEdit", selectedItem);
                    MainWindowViewModel.Instance.NavigateWithParam("LightEdit", parameters);
                    break;
                case SceneType.Material:
                    parameters.Add("MaterialEdit", selectedItem);
                    MainWindowViewModel.Instance.NavigateWithParam("MaterialEdit", parameters);
                    break;
                case SceneType.Texture:
                    parameters.Add("TextureEdit", selectedItem);
                    MainWindowViewModel.Instance.NavigateWithParam("TextureEdit", parameters);
                    break;
                default:
                    break;
            }
        }
    }
}
