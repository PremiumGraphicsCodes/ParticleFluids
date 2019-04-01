namespace PG.CGStudio.Texture
{
    public class TextureObjectRepository
    {
        private PG.CLI.TextureObjectRepositoryAdapter Adapter { get; }

        public TextureObjectRepository()
        {
            this.Adapter = new PG.CLI.TextureObjectRepositoryAdapter();
        }

        public int Add(PG.Core.Graphics.Texture texture)
        {
            return Adapter.Add(texture);
        }
    }
}
