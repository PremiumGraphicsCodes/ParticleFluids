using System.Xml.Linq;
using PG.Core.Shape;

namespace PG.Scene
{
    public class ParticleSystemScene : ISceneNode
    {
        private ParticleSystem shape;

        public override string Name { get; }

        public ParticleSystemScene()
        {
        }

        public ParticleSystemScene(ParticleSystem shape)
        {
            this.shape = shape;
        }

        /*
        public override void FromElement(XElement element)
        {
            var Name = element.Value;
        }

        public override XElement ToElement()
        {
            var element = new XElement("ParticleSystem");
            element.Add(new XElement("Name",Name));
            element.Add(new XElement("Name",Name));
            return element;
        }
        */
    }
}
