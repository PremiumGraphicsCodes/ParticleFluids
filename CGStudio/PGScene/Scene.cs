using System.Xml;
using System.Xml.Linq;

namespace PG.Scene
{
    public class Scene
    {
        public RootScene Root { get; }

        public Scene()
        {
            this.Root = new RootScene();
        }

        /*
        public void Add(ISceneNode parent, ISceneNode child)
        {
            parent.Children.Add(child);
        }
        */

        public XDocument ToDocument()
        {
            var document = new XDocument();
            document.Add(new XElement("Root", new XAttribute("name", "value")) );
            foreach(var child in Root.Children)
            {
                ;
                //child.Add()
            }
            document.Add(new XElement("Child", "text node"));
            return document;
        }
    }
}
