using PG.Core;
using PG.Core.Math;

namespace PG.CGStudio
{
    public class MainModel
    {
        private World world;

        public World World { get { return world; } }

        public MainModel()
        {
            world = new World();
        }

    }
}
