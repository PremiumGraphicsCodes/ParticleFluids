using PG.Core.Math;

namespace PG.Core.Shape.Glyph
{
    public class ArrowGlyph3d : IGlyph3d
    {
        Cylinder3d cylider;
        Cone3d cone;

        public ArrowGlyph3d(Vector3d origin, Vector3d direction)
        {
            this.cylider = new Cylinder3d();
            this.cone = new Cone3d();
        }

        public void Build()
        {
        }

        //public WireFrame ToWireFrame();
    }
}
