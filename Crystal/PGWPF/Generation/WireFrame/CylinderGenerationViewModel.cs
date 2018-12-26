using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;

namespace PG.CGStudio.Generation.WireFrame
{
    public class CylinderGenerationViewModel
    {
        public Cylinder3dViewModel CylinderViewModel { get; }
            = new Cylinder3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public CylinderGenerationViewModel()
        {
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var cylinder = CylinderViewModel.Value;
            builder.Build(cylinder, 25, 25);
            var wireFrame = builder.WireFrame;
            MainModel.Instance.Add(wireFrame);
            Canvas3dView.Instance.Update(MainModel.Instance);
            Canvas3dView.Instance.Render();
        }
    }
}
