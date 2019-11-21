using PG.Core.Shape;
using Reactive.Bindings;
using PG.Control;
using PG.Control.Math;
using Prism.Mvvm;
using PG.Core.UI;
using PG.Core.Graphics;

namespace PG.CGStudio.Generation.WireFrame
{
    public class BoxGenerationViewModel : BindableBase
    {
        public Box3dViewModel BoxViewModel { get; }

        public AppearanceViewModel AppearanceViewModel { get; }

        public ReactiveCommand GenerationCommand { get; }

        public BoxGenerationViewModel()
        {
            this.BoxViewModel = new Box3dViewModel();
            this.AppearanceViewModel = new AppearanceViewModel();
            this.GenerationCommand = new ReactiveCommand();
            this.GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new WireFrameBuilder();
            var box = BoxViewModel.Value;
            builder.Build(box);
            var wireFrame = builder.WireFrame;
            var appearance = AppearanceViewModel.Value;
            MainModel.Instance.World.Scenes.AddWireFrameScene(wireFrame, "WFBox", appearance);
            Canvas3d.Instance.Update(MainModel.Instance.World);
            Canvas3d.Instance.Render();
        }
    }
}
