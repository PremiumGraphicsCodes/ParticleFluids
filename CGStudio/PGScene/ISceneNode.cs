﻿using System.Collections.Generic;
using System.Xml.Linq;

namespace PG.Scene
{
    public abstract class ISceneNode
    {
        public List<ISceneNode> Children { get; set; }

        /*
        public abstract XElement ToElement();

        public abstract void FromElement(XElement element);
        */
    }
}
