using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;
using PG.Control.Math;
using Prism.Mvvm;
using PG.Core.UI;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }
            = new Box3dViewModel();

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public BoxGenerationViewModel()
        {
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var box = BoxViewModel.Value;
            builder.Build(box);
            var wireFrame = builder.WireFrame;
            //MainModel.Instance.Repository.AddWireFrameScene(wireFrame.Li, "WFBox");
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
        }
    }
}
