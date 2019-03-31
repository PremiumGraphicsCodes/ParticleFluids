using PG.Control;
using PG.Control.Math;
using PG.Core.Shape;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.CGStudio.Generation.PolygonMesh
{
    public class SphereGenerationViewModel : BindableBase
    {
        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<int> VNum { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand ExecuteCommand { get; }
            = new ReactiveCommand();

        public Sphere3dViewModel SphereViewModel { get; }
            = new Sphere3dViewModel();

        public SphereGenerationViewModel()
        {
            this.UNum.Value = 24;
            this.VNum.Value = 24;
            this.ExecuteCommand.Subscribe(OnExecute);
        }
  
        private void OnExecute()
        {
            var builder = new PolygonMeshBuilder();
            builder.Build(SphereViewModel.Value, UNum.Value, VNum.Value);
            MainModel.Instance.Repository.Objects.Add(builder.PolygonMesh);
            OpenGLPresenter.Instance.Update(MainModel.Instance.Repository);
            OpenGLPresenter.Instance.Render();
        }
    }
}
