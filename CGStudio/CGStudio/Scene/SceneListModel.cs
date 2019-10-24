using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.CGStudio.Scene
{
    public class SceneListModel
    {
        private PG.CLI.WorldAdapter adapter;

        public ReactiveCollection<SceneModel> Scenes;

        public SceneListModel(PG.CLI.WorldAdapter adapter)
        {
            this.adapter = adapter;
            this.Scenes = new ReactiveCollection<SceneModel>();
            this.Scenes.Add( CreateRoot() );
        }

        private SceneModel CreateRoot()
        {
            var root = new SceneModel();
            root.Id.Value = 0;
            root.Name.Value = "Root";
            return root;
        }

        public int AddParticleSystemScene(List<Vector3d> positions, string name, Core.UI.ParticleAppearance appearance)
        {
            var command = new PG.CLI.Command(PG.ParticleSystemAddLabels.ParticleSystemAddLabel);
            command.SetArg(PG.ParticleSystemAddLabels.PositionsLabel, positions);
            command.SetArg(PG.ParticleSystemAddLabels.NameLabel, name);
            command.SetArg(PG.ParticleSystemAddLabels.PointSizeLabel, appearance.Size);
            command.SetArg(PG.ParticleSystemAddLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.ParticleSystemAddLabels.IsItemLabel, false);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.ParticleSystemAddLabels.NewIdLabel);

            command.Create(PG.CameraLabels.CameraFitCommandLabel);
            command.Execute(adapter);
            command.Clear();
            Sync();
            return newId;
        }

        public int AddWireFrameScene(List<Line3d> lines, string name, Core.UI.WireAppearance appearance)
        {
            var command = new PG.CLI.Command(PG.WireFrameAddLabels.WireFrameAddLabel);
            command.SetArg(PG.WireFrameAddLabels.LinesLabel, lines);
            command.SetArg(PG.WireFrameAddLabels.NameLabel, name);
            command.SetArg(PG.WireFrameAddLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.WireFrameAddLabels.LineWidthLabel, appearance.Width);
            command.SetArg(PG.WireFrameAddLabels.IsItemLabel, false);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.WireFrameAddLabels.NewIdLabel);

            command.Create(PG.CameraLabels.CameraFitCommandLabel);
            command.Execute(adapter);
            command.Clear();

            Sync();
            return newId;
        }

        public int AddPolygonMeshScene(PolygonMesh polygonMesh, string name)
        {
            var command = new PG.CLI.Command("PolygonMeshAdd");
            //            command.SetArg("Lines", lines);
            //            command.SetArg("Name", name);
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        public int AddMaterialScene(PG.Core.Graphics.Material material, string name)
        {
            var command = new PG.CLI.Command("MaterialAdd");
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        public int AddLightScene(PG.Core.Graphics.PointLight light, string name)
        {
            var command = new PG.CLI.Command("LightAdd");
            command.Execute(adapter);
            var newId = command.GetResult<int>("NewId");
            Sync();
            return newId;
        }

        public void Sync()
        {
            var ids = PG.CLI.Command.Get<List<int>>(adapter, PG.GetLabels.SceneListIdsLabel);
            this.Scenes.Clear();
            var root = CreateRoot();
            foreach (var id in ids)
            {
                var s = new SceneModel();
                s.Id.Value = id;
                s.Name.Value = PG.CLI.Command.Get<string>(adapter, GetLabels.NameLabel, id);
                s.IsVisible.Value = PG.CLI.Command.Get<bool>(adapter, GetLabels.IsVisibleLabel, id);
                root.Children.Add(s);
            }
            Scenes.Add( root );

            //var newScene = this.adapter.GetSceneAdapter().ToScene();
        }
        /*

        public SceneType GetTypeById(int id)
        {
            var type = (SceneType)this.adapter.GetSceneAdapter().GetTypeById(id);
            return type;
        }
        */

    }
}
