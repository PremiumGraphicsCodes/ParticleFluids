using System.Collections.Generic;

namespace PG.Core
{
    public enum SceneType
    {
        None,
        Root,
        ParticleSystem,
        WireFrame,
        PolygonMesh,
        Solid,
//        ShapeScene = 0x02 | 0x04 | 0x08,
        Material,
        PointLight,
        Texture,
        FaceGroup,
        AllScene,
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
