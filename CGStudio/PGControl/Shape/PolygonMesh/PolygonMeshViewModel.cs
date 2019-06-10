using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Shape
{
    public class PolygonMeshViewModel : BindableBase
    {
        public ReactiveProperty<int> Id;

        public ReactiveProperty<string> Name;

        public ReactiveProperty<int> VertexCount;

        public ReactiveProperty<int> FaceCount;

        public ReactiveProperty<int> FaceGroupCount;

        public PolygonMeshViewModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.VertexCount = new ReactiveProperty<int>();
            this.FaceCount = new ReactiveProperty<int>();
            this.FaceGroupCount = new ReactiveProperty<int>();
        }
    }
}
