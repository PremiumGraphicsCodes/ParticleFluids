namespace PG.CGStudio
{
    public class MainModel
    {
        static MainModel instance;

        public static MainModel Instance { get { return instance; } }

        private World repository;

        public World Repository { get { return repository; } }

        public MainModel()
        {
            instance = this;
            repository = new World();
        }
    }
}
