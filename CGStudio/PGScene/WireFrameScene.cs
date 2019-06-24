using PG.Core.Shape;

namespace PG.Scene
{
    public class WireFrameScene : ISceneNode
    {
        private WireFrame shape;

        public string Name;

        public WireFrameScene()
        {
        }

        public WireFrameScene(WireFrame shape)
        {
            this.shape = shape;
        }
    }
}
