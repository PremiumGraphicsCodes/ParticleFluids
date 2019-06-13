using PG.CLI;
using PG.Core.Math;

namespace PG.CGStudio
{
    public class Camera
    {
        private CameraAdapter Adapter { get; }

        public Camera(CameraAdapter adapter)
        {
            this.Adapter = adapter;
        }

        Matrix4d ProjectionMatrix
        {
            get { return Adapter.ProjectionMatrix(); }
        }
    }
}
