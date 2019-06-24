using System.Collections.Generic;

namespace PG.Scene
{
    public class RootScene : ISceneNode
    {
        public RootScene()
        {
            this.Children = new List<ISceneNode>();
        }
    }
}
