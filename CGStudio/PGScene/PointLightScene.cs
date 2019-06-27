using PG.Core.Graphics;

namespace PG.Scene
{
    public class PointLightScene : ISceneNode
    {
        private PointLight light { get; }

        public override string Name { get; }

        public PointLightScene()
        {
        }

        public PointLightScene(PointLight light)
        {
            this.light = light;
        }
    }
}
