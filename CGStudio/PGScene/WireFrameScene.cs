using PG.Core.Shape;

namespace PG.Scene
{
    public class WireFrameScene : ISceneNode
    {
        private WireFrame shape;

        public override string Name { get; }

        public WireFrameScene()
        {
        }

        public WireFrameScene(WireFrame shape)
        {
            this.shape = shape;
        }
    }
}
