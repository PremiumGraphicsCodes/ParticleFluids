using Reactive.Bindings;
using PG.Scene;
using Prism.Regions;
using Prism.Mvvm;
using PG.Core;

namespace PG.CGStudio
{
    public class SceneListViewModel : BindableBase
    {
        public ReadOnlyReactiveCollection<SceneModel> Items { get; }

        private readonly IRegionManager regionManager;

        private readonly SceneList world;

        public SceneListViewModel(IRegionManager regionManager, SceneList world)
        {
            this.world = world;
            this.regionManager = regionManager;
            Items = world.Scenes.ToReadOnlyReactiveCollection();
        }

        private void NavigateView(string name, NavigationParameters navigationParameters)
        {
            regionManager.RequestNavigate("ContentRegion", name, navigationParameters);
        }

        public void ChangeView(SceneModel selectedItem)
        {
            if (selectedItem == null)
            {
                return;
            }
            var parameters = new NavigationParameters();
            parameters.Add("Id", selectedItem.Id.Value);
            var command = new PG.CLI.Command(SceneGetLabels.CommandLabel);
            command.SetArg(SceneGetLabels.IdLabel, selectedItem.Id.Value);
            command.Execute(world.Adapter);
            var type = command.GetResult<SceneType>(SceneGetLabels.TypeLabel);
            switch (type)
            {
                case SceneType.ParticleSystem:
                    parameters.Add("ParticleSystemEdit", selectedItem);
                    NavigateView("ParticleSystemEdit", parameters);
                    break;
                case SceneType.WireFrame:
                    parameters.Add("WireFrameEdit", selectedItem);
                    NavigateView("WireFrameEdit", parameters);
                    break;
                case SceneType.PolygonMesh:
                    parameters.Add("PolygonMeshEdit", selectedItem);
                    NavigateView("PolygonMeshEdit", parameters);
                    break;
                case SceneType.FaceGroup:
                    parameters.Add("FaceGroupEdit", selectedItem);
                    NavigateView("FaceGroupEdit", parameters);
                    break;
                case SceneType.PointLight:
                    parameters.Add("LightEdit", selectedItem);
                    NavigateView("LightEdit", parameters);
                    break;
                case SceneType.Material:
                    parameters.Add("MaterialEdit", selectedItem);
                    NavigateView("MaterialEdit", parameters);
                    break;
                case SceneType.Texture:
                    parameters.Add("TextureEdit", selectedItem);
                    NavigateView("TextureEdit", parameters);
                    break;
                default:
                    break;
            }
        }
    }
}
