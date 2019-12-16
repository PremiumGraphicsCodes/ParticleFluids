using System.Collections.Generic;

namespace PG.Core
{
    public enum SceneType
    {
        None = 0x00,
        Root = 0x01,
        ParticleSystem = 0x02,
        WireFrame = 0x04,
        PolygonMesh = 0x08,
        ShapeScene = 0x02 | 0x04 | 0x08,
        Material = 0x10,
        PointLight = 0x20,
        Texture = 0x40,
        FaceGroup = 0x80,
        AllScene = 0xFF,
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
