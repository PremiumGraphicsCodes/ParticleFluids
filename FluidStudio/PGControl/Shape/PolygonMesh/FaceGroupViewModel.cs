using PG.Control.Graphics;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Shape
{
    public class FaceGroupViewModel : BindableBase
    {
        public ReactiveProperty<int> Id;

        public ReactiveProperty<int> FaceCount;

        public MaterialViewModel MaterialViewModel;

        public FaceGroupViewModel()
        {
            Id = new ReactiveProperty<int>();
            FaceCount = new ReactiveProperty<int>();
            MaterialViewModel = new MaterialViewModel();
        }
    }
}