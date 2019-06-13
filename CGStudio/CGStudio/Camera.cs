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

        public Matrix4d ModelViewMatrix
        {
            get { return Adapter.ModelViewMatrix(); }
        }

        public Matrix4d ProjectionMatrix
        {
            get { return Adapter.ProjectionMatrix(); }
        }
    }
}
