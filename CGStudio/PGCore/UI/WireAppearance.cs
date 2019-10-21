using PG.Core.Graphics;

namespace PG.Core.UI
{
    public class WireAppearance
    {
        public ColorRGBA Color { get; set; }
            = new ColorRGBA();

        public float Width { get; set; }

        public WireAppearance()
        {
            this.Width = 1.0f;
        }
    }
}