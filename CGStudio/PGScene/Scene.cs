using System.Collections.Generic;
using System.Xml;
using System.Xml.Linq;

namespace PG.Scene
{
    public enum SceneType
    {
        None,
        Root,
        ParticleSystem,
        WireFrame,
        PolygonMesh,
        PointLight,
    }

    public class Scene : IScene
    {
        public int Id { get; }

        public virtual string Name { get; }

        public List<IScene> Children { get; set; }

        public SceneType Type { get; }

        public Scene(int id, string name, SceneType type) :
            base(id, name, SceneType.Root)
        {
            this.Id = id;
            this.Name = name;
            this.Type = type;
            Children = new List<IScene>();
        }
    }
}
