using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

using Prism.Regions;

using PG.Core;
using PG.Scene;

namespace PG.CGStudio.Object
{
    public class SceneListViewBehavior : Behavior<TreeView>
    {
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
            if (e.Key == Key.Delete)
            {
                World.Instance.Scenes.Delete(selectedItem.Id.Value);
            }
        }

        private void ItemDoubleClicked(object sender, MouseButtonEventArgs e)
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
            var parameters = new NavigationParameters();
            parameters.Add("Id", selectedItem.Id.Value);
            var command = new PG.CLI.Command(SceneGetLabels.CommandLabel);
            command.SetArg(SceneGetLabels.IdLabel, selectedItem.Id.Value);
            command.Execute(World.Instance.Adapter);
            var type = command.GetResult<SceneType>(SceneGetLabels.TypeLabel);
            switch(type)
            {
                case SceneType.ParticleSystem:
                    parameters.Add("ParticleSystemEdit", selectedItem);
                    RequestNavigate("ParticleSystemEdit", parameters);
                    break;
                case SceneType.WireFrame:
                    parameters.Add("WireFrameEdit", selectedItem);
                    RequestNavigate("WireFrameEdit", parameters);
                    break;
                case SceneType.PolygonMesh:
                    parameters.Add("PolygonMeshEdit", selectedItem);
                    RequestNavigate("PolygonMeshEdit", parameters);
                    break;
                case SceneType.FaceGroup:
                    parameters.Add("FaceGroupEdit", selectedItem);
                    RequestNavigate("FaceGroupEdit", parameters);
                    break;
                case SceneType.PointLight:
                    parameters.Add("LightEdit", selectedItem);
                    RequestNavigate("LightEdit", parameters);
                    break;
                case SceneType.Material:
                    parameters.Add("MaterialEdit", selectedItem);
                    RequestNavigate("MaterialEdit", parameters);
                    break;
                case SceneType.Texture:
                    parameters.Add("TextureEdit", selectedItem);
                    RequestNavigate("TextureEdit", parameters);
                    break;
                default:
                    break;
            }
        }

        private void RequestNavigate(string name, NavigationParameters parameters)
        {
            MainWindowViewModel.Instance.NavigateWithParam(name, parameters);
        }
    }
}
