using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Core;
using PG.Scene;
using Reactive.Bindings;

namespace PG.Control.UI
{
    public class SceneSelectViewModel
    {
        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveCommand SceneSelectCommand { get; }
            = new ReactiveCommand();

        private readonly SceneList scenes;

        private readonly Canvas3d canvas;

        public SceneSelectViewModel(SceneList scenes, Canvas3d canvas)
        {
            this.scenes = scenes;
            this.canvas = canvas;
            this.SceneSelectCommand.Subscribe(OnSelect);
        }

        private void OnSelect()
        {
            var picker = new PickUICtrl(scenes, canvas, 10, Core.SceneType.AllScene);
            picker.AddAction(OnPick);
            this.canvas.UICtrl = picker;
        }

        private void OnPick(SceneId id)
        {
            this.Id.Value = id.parentId;
        }
    }
}
