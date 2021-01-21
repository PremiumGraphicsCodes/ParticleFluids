using System.Collections.Generic;

namespace PG.Core
{
    public class SceneType
    {
        public const string None = "None";
        public const string Root = "Root";
        public const string ParticleSystem = "ParticleSystem";
        public const string WireFrame = "WireFrame";
        public const string PolygonMesh = "PolygonMesh";
        public const string Solid = "Solid";

        public enum Type
        {
            None,
            Root,
            ParticleSystem,
            WireFrame,
            PolygonMesh,
            Solid,
            Material,
            PointLight,
            Texture,
            FaceGroup,
            AllScene,
        }

        public string TypeName { get; }

        public SceneType()
        {
            TypeName = None;
        }

        public SceneType(Type type)
        {
            switch (type)
            {
                case Type.None:
                    {
                        TypeName = None;
                        break;
                    }
                case Type.ParticleSystem:
                    {
                        TypeName = ParticleSystem;
                        break;
                    }
                case Type.WireFrame:
                    {
                        TypeName = WireFrame;
                        break;
                    }
                case Type.PolygonMesh:
                    {
                        TypeName = PolygonMesh;
                        break;
                    }
                case Type.Solid:
                    {
                        TypeName = Solid;
                        break;
                    }
                default:
                    {
                        System.Diagnostics.Debug.Assert(false);
                        break;
                    }
            }
        }

        public SceneType(string typeName)
        {
            this.TypeName = typeName;
        }
    }

    public class Scene
    {
        public int Id { get; }

        public string Name { get; }

        public List<Scene> Children { get; set; }

        public SceneType Type { get; }

        public Scene(int id, string name, SceneType type)
        {
            this.Id = id;
            this.Name = name;
            this.Type = type;
            Children = new List<Scene>();
        }

        public void Clear()
        {
            Children.Clear();
        }
    }

}
