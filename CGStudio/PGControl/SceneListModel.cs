using PG.Core;
using PG.Core.Graphics;
using PG.Core.Math;
using PG.Core.Shape;
using PG.Core.UI;
using Reactive.Bindings;
using System.Collections.Generic;

namespace PG.Scene
{
    public class SceneListModel
    {
        private PG.CLI.WorldAdapter adapter;

        public ReactiveCollection<SceneModel> Scenes;

        public SceneListModel(PG.CLI.WorldAdapter adapter)
        {
            this.adapter = adapter;
            this.Scenes = new ReactiveCollection<SceneModel>();
            this.Scenes.Add(CreateRoot());
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

            /*
            if (layer > 0)
            {
                command.Create(PG.CameraLabels.CameraFitCommandLabel);
                command.Execute(adapter);
                command.Clear();
                Sync();
            }
            */
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

            if (layer > 0)
            {
                command.Create(PG.CameraLabels.CameraFitCommandLabel);
                command.Execute(adapter);
                command.Clear();

                Sync();
            }
            return newId;
        }

        public void SetMatrix(int id, Matrix4d matrix)
        {
            var command = new PG.CLI.Command(SetMatrixLabels.CommandLabel);
            command.SetArg(SetMatrixLabels.IdLabel, id);
            command.SetArg(SetMatrixLabels.MatrixLabel, matrix);
            command.Execute(adapter);
        }

        public void Transform(int id, Matrix4d matrix)
        {
            var command = new PG.CLI.Command(TransformLabels.TransformCommandLabel);
            command.SetArg(TransformLabels.IdLabel, id);
            command.SetArg(TransformLabels.MatrixLabel, matrix);
            command.Execute(adapter);
        }

        public int AddMaterialScene(PG.Core.Graphics.Material material, string name)
        {
            var command = new PG.CLI.Command(PG.MaterialCreateLabels.CommandNameLabel);
            command.SetArg(PG.MaterialCreateLabels.AmbientLabel, material.Ambient);
            command.SetArg(PG.MaterialCreateLabels.DiffuseLabel, material.Diffuse);
            command.SetArg(PG.MaterialCreateLabels.SpecularLabel, material.Specular);
            command.SetArg(PG.MaterialCreateLabels.ShininessLabel, material.Shininess);
            //            command.SetArg(PG.MaterialCreateLabels.TextureIdLabel, material.TextureId);
            command.SetArg(PG.MaterialCreateLabels.NameLabel, name);
            //            command.SetArg(PG.MaterialCreateLabels.TextureIdLabel, material.)
            command.Execute(adapter);
            var newId = command.GetResult<int>(PG.MaterialCreateLabels.NewIdLabel);
            Sync();
            return newId;
        }

        public PG.Core.Graphics.Material GetMaterialScene(int id)
        {
            var command = new PG.CLI.Command(PG.MaterialGetLabels.CommandNameLabel);
            command.SetArg(PG.MaterialGetLabels.IdLabel, id);
            command.Execute(adapter);
            var m = new PG.Core.Graphics.Material
            {
                Ambient = command.GetResult<ColorRGBA>(PG.MaterialGetLabels.AmbientLabel),
                Diffuse = command.GetResult<ColorRGBA>(PG.MaterialGetLabels.DiffuseLabel),
                Specular = command.GetResult<ColorRGBA>(PG.MaterialGetLabels.SpecularLabel),
                Shininess = command.GetResult<float>(PG.MaterialGetLabels.ShininessLabel)
            };
            return m;
        }

        public void SetMaterialScene(PG.Core.Graphics.Material material, string name, int id)
        {
            var command = new PG.CLI.Command(PG.MaterialSetLabels.CommandNameLabel);
            command.SetArg(PG.MaterialSetLabels.IdLabel, id);
            command.SetArg(PG.MaterialSetLabels.AmbientLabel, material.Ambient);
            command.SetArg(PG.MaterialSetLabels.DiffuseLabel, material.Diffuse);
            command.SetArg(PG.MaterialSetLabels.SpecularLabel, material.Specular);
            command.SetArg(PG.MaterialSetLabels.ShininessLabel, material.Shininess);
            command.SetArg(PG.MaterialSetLabels.NameLabel, name);
            command.Execute(adapter);
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

        public void SetLightScene(PointLight light, string name, int id)
        {
            var command = new PG.CLI.Command(PG.LightSetLabels.CommandNameLabel);
            command.SetArg(PG.LightSetLabels.IdLabel, id);
            command.SetArg(PG.LightSetLabels.AmbientLabel, light.Ambient);
            command.SetArg(PG.LightSetLabels.DiffuseLabel, light.Diffuse);
            command.SetArg(PG.LightSetLabels.SpecularLabel, light.Specular);
            command.SetArg(PG.LightSetLabels.PositionLabel, light.Position);
            command.SetArg(PG.LightSetLabels.NameLabel, name);
            command.Execute(adapter);
        }

        public PointLight GetLightScene(int id)
        {
            var command = new PG.CLI.Command(PG.LightGetLabels.CommandNameLabel);
            command.SetArg(PG.LightGetLabels.IdLabel, id);
            command.Execute(adapter);

            var light = new PointLight
            {
                Position = command.GetResult<Vector3d>(PG.LightGetLabels.PositionLabel),
                Ambient = command.GetResult<ColorRGBA>(PG.LightGetLabels.AmbientLabel),
                Diffuse = command.GetResult<ColorRGBA>(PG.LightGetLabels.DiffuseLabel),
                Specular = command.GetResult<ColorRGBA>(PG.LightGetLabels.SpecularLabel)
            };
            return light;
        }

        public int AddTextureScene(string imageFilePath, string name)
        {
            var command = new PG.CLI.Command(PG.TextureCreateLabels.CommandNameLabel);
            command.SetArg(PG.TextureCreateLabels.FilePathLabel, imageFilePath);
            command.SetArg(PG.TextureCreateLabels.NameLabel, name);

            /*
            Canvas3d.Instance.Renderer.Bind();
            command.Execute(adapter);
            Canvas3d.Instance.Renderer.UnBind();
            */

            var newId = command.GetResult<int>(PG.TextureCreateLabels.NewIdLabel);
            Sync();
            return newId;
        }

        public Box3d GetBoundingBox(int id)
        {
            var command = new PG.CLI.Command(PG.SceneGetLabels.CommandLabel);
            command.SetArg(PG.SceneGetLabels.IdLabel, id);
            command.Execute(adapter);
            return command.GetResult<Box3d>(PG.SceneGetLabels.BoundingBoxLabel);
        }

        public Vector3d GetCenter(int id)
        {
            return GetBoundingBox(id).Center;
        }

        public void Delete(int id, bool isItem = false)
        {
            var command = new PG.CLI.Command(PG.DeleteLabels.CommandNameLabel);
            command.SetArg(PG.DeleteLabels.IdLabel, id);
            command.SetArg(PG.DeleteLabels.IsItemLabel, isItem);
            command.Execute(adapter);
            Sync();
        }

        public void Clear(int layer)
        {
            var command = new PG.CLI.Command(PG.ClearLabels.CommandNameLabel);
            command.SetArg(PG.ClearLabels.LayerLabel, layer);
            command.Execute(adapter);
            Sync();
        }

        public void ShowBoundingBox(int id)
        {
            var bb = GetBoundingBox(id);
            var builder = new WireFrameBuilder();
            builder.Add(bb);
            var appearance = new WireAppearance();
            appearance.Color = new Core.Graphics.ColorRGBA(1.0f, 0.0f, 0.0f, 0.0f);
            AddWireFrameScene(builder.ToWireFrame(), "", appearance, 0);
            /*
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
            */
        }

        public Vector3d GetPosition(ObjectId id)
        {
            var command = new PG.CLI.Command(PG.PositionGetLabels.CommandNameLabel);
            command.SetArg(PG.PositionGetLabels.ParentIdLabel, id.parentId);
            command.SetArg(PG.PositionGetLabels.ChildIdLabel, id.childId);
            command.Execute(adapter);
            return command.GetResult<Vector3d>(PG.PositionGetLabels.PositionLabel);
        }

        public void Sync()
        {
            var ids = PG.CLI.Command.Get<List<int>>(adapter, PG.GetLabels.SceneListIdsLabel);
            this.Scenes.Clear();
            var root = CreateRoot();
            foreach (var id in ids)
            {
                var s = new SceneModel();

                var command = new PG.CLI.Command(PG.SceneGetLabels.CommandLabel);
                command.SetArg(PG.SceneGetLabels.IdLabel, id);
                command.Execute(adapter);

                s.Id.Value = id;
                s.Name.Value = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
                s.IsVisible.Value = command.GetResult<bool>(PG.SceneGetLabels.IsVisibleLabel);
                var childIds = PG.CLI.Command.Get<List<int>>(adapter, PG.GetLabels.SceneListIdsLabel, id);
                foreach (var childId in childIds)
                {
                    var ss = new SceneModel();
                    ss.Id.Value = childId;

                    var command2 = new PG.CLI.Command(PG.SceneGetLabels.CommandLabel);
                    command2.SetArg(PG.SceneGetLabels.IdLabel, id);
                    command2.Execute(adapter);

                    ss.Name.Value = command.GetResult<string>(PG.SceneGetLabels.NameLabel);
                    ss.IsVisible.Value = command.GetResult<bool>(PG.SceneGetLabels.IsVisibleLabel);
                    s.Children.Add(ss);
                }
                root.Children.Add(s);
            }
            Scenes.Add(root);

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
