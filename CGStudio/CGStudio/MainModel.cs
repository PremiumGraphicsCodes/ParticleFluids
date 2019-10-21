namespace PG.CGStudio
{
    public class MainModel
    {
        static MainModel instance;

        public static MainModel Instance { get { return instance; } }

        private World world;

        public World World { get { return world; } }

        public MainModel()
        {
            instance = this;
            world = new World();
        }
    }
}
