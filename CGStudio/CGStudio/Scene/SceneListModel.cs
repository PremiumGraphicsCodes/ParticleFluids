using PG.CGStudio.Scene.Shape;
using PG.Core;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
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

        public int AddParticleSystemScene(List<Vector3d> positions, string name, Core.UI.ParticleAppearance appearance, int layer)
        {
            var command = new PG.CLI.Command(PG.ParticleSystemCreateLabels.ParticleSystemAddLabel);
            command.SetArg(PG.ParticleSystemCreateLabels.PositionsLabel, positions);
            command.SetArg(PG.ParticleSystemCreateLabels.NameLabel, name);
            command.SetArg(PG.ParticleSystemCreateLabels.PointSizeLabel, appearance.Size);
            command.SetArg(PG.ParticleSystemCreateLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.ParticleSystemCreateLabels.LayerLabel, layer);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.ParticleSystemCreateLabels.NewIdLabel);

            if (layer > 0)
            {
                command.Create(PG.CameraLabels.CameraFitCommandLabel);
                command.Execute(adapter);
                command.Clear();
                Sync();
            }
            return newId;
        }

        public int AddWireFrameScene(WireFrame wireFrame, string name, Core.UI.WireAppearance appearance, int layer)
        {
            var command = new PG.CLI.Command(PG.WireFrameCreateLabels.WireFrameAddLabel);
            command.SetArg(PG.WireFrameCreateLabels.PositionsLabel, wireFrame.Positions);
            command.SetArg(PG.WireFrameCreateLabels.EdgesLabel, wireFrame.Edges);
            command.SetArg(PG.WireFrameCreateLabels.NameLabel, name);
            command.SetArg(PG.WireFrameCreateLabels.ColorLabel, appearance.Color);
            command.SetArg(PG.WireFrameCreateLabels.LineWidthLabel, appearance.Width);
            command.SetArg(PG.WireFrameCreateLabels.LayerLabel, layer);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.WireFrameCreateLabels.NewIdLabel);

            if (layer > 0)
            {
                command.Create(PG.CameraLabels.CameraFitCommandLabel);
                command.Execute(adapter);
                command.Clear();

                Sync();
            }
            return newId;
        }

        public int AddPolygonMeshScene(PolygonMesh polygon, string name, int layer)
        {
            var command = new PG.CLI.Command(PG.PolygonMeshCreateLabels.CommandNameLabel);
            command.SetArg(PG.PolygonMeshCreateLabels.PositionsLabel, polygon.Positions);
            command.SetArg(PG.PolygonMeshCreateLabels.NormalsLabel, polygon.Normals);
            command.SetArg(PG.PolygonMeshCreateLabels.TexCoordsLabel, polygon.TexCoords);
            command.SetArg(PG.PolygonMeshCreateLabels.VerticesLabel, polygon.Vertices);
            command.SetArg(PG.PolygonMeshCreateLabels.FacesLabel, polygon.Faces);
            command.SetArg(PG.PolygonMeshCreateLabels.NameLabel, name);
            command.SetArg(PG.PolygonMeshCreateLabels.LayerLabel, layer);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.PolygonMeshCreateLabels.NewIdLabel);
            command.Clear();

            if (layer > 0) {
                command.Create(PG.CameraLabels.CameraFitCommandLabel);
                command.Execute(adapter);
                command.Clear();

                Sync();
            }
            return newId;

        }

        public int AddMaterialScene(PG.Core.Graphics.Material material, string name)
        {
            var command = new PG.CLI.Command(PG.MaterialCreateLabels.CommandNameLabel);
            command.SetArg(PG.MaterialCreateLabels.AmbientLabel, material.Ambient);
            command.SetArg(PG.MaterialCreateLabels.DiffuseLabel, material.Diffuse);
            command.SetArg(PG.MaterialCreateLabels.SpecularLabel, material.Specular);
            command.SetArg(PG.MaterialCreateLabels.ShininessLabel, material.Shininess);
            command.SetArg(PG.MaterialCreateLabels.TextureIdLabel, material.TextureId);
            command.SetArg(PG.MaterialCreateLabels.NameLabel, name);
//            command.SetArg(PG.MaterialCreateLabels.TextureIdLabel, material.)
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.MaterialCreateLabels.NewIdLabel);
            Sync();
            return newId;
        }

        public int AddLightScene(PG.Core.Graphics.PointLight light, string name)
        {
            var command = new PG.CLI.Command(PG.LightCreateLabels.CommandNameLabel);
            command.SetArg(PG.LightCreateLabels.PositionLabel, light.Position);
            command.SetArg(PG.LightCreateLabels.AmbientLabel, light.Ambient);
            command.SetArg(PG.LightCreateLabels.DiffuseLabel, light.Diffuse);
            command.SetArg(PG.LightCreateLabels.SpecularLabel, light.Specular);
            command.SetArg(PG.LightCreateLabels.NameLabel, name);
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.LightCreateLabels.NewIdLabel);
            Sync();
            return newId;
        }

        public void UpdateLightScene(PG.Core.Graphics.PointLight light, string name, int id)
        {
            PG.CLI.Command.Set(adapter, PG.SetLabels.NameLabel, id, name);
            PG.CLI.Command.Set(adapter, PG.SetLabels.AmbientLabel, id, light.Ambient);
            PG.CLI.Command.Set(adapter, PG.SetLabels.DiffuseLabel, id, light.Diffuse);
            PG.CLI.Command.Set(adapter, PG.SetLabels.SpecularLabel, id, light.Specular);
            PG.CLI.Command.Set(adapter, PG.SetLabels.PositionLabel, id, light.Position);
        }

        public int AddTextureScene(string imageFilePath, string name)
        {
            var command = new PG.CLI.Command(PG.TextureCreateLabels.CommandNameLabel);
            command.SetArg(PG.TextureCreateLabels.FilePathLabel, imageFilePath);
            command.SetArg(PG.TextureCreateLabels.NameLabel, name);

            Canvas3d.Instance.Renderer.Bind();
            command.Execute(adapter);
            Canvas3d.Instance.Renderer.UnBind();

            var newId = command.GetResult<int>(PG.TextureCreateLabels.NewIdLabel);
            Sync();
            return newId;
        }

        public void Delete(int id)
        {
            var command = new PG.CLI.Command(PG.DeleteLabels.CommandNameLabel);
            command.SetArg(PG.DeleteLabels.IdLabel, id);
            command.SetArg(PG.DeleteLabels.IsItemLabel, false);
            command.Execute(adapter);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
            Sync();
        }

        public void Clear(int layer)
        {
            var command = new PG.CLI.Command(PG.ClearLabels.CommandNameLabel);
            command.SetArg(PG.ClearLabels.LayerLabel, layer);
            command.Execute(adapter);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
            Sync();
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
                var childIds = PG.CLI.Command.Get<List<int>>(adapter, PG.GetLabels.SceneListIdsLabel, id);
                foreach(var childId in childIds)
                {
                    var ss = new SceneModel();
                    ss.Id.Value = childId;
                    ss.Name.Value = PG.CLI.Command.Get<string>(adapter, GetLabels.NameLabel, childId);
                    ss.IsVisible.Value = PG.CLI.Command.Get<bool>(adapter, GetLabels.IsVisibleLabel, childId);
                    s.Children.Add(ss);
                }
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
