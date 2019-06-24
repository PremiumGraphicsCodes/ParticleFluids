namespace PG.CGStudio.Light
{
    public class LightObjectRepository
    {
        private PG.CLI.LightObjectRepositoryAdapter adapter;

        public LightObjectRepository()
        {
            this.adapter = new PG.CLI.LightObjectRepositoryAdapter();
        }

        public int Add(PG.Core.Graphics.PointLight light)
        {
            return adapter.Add(light);
        }
    }
}
