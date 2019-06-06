using Prism.Mvvm;
using Reactive.Bindings;
using System;

namespace PG.CGStudio
{
    public class ObjectModel : BindableBase
    {
        public ReactiveProperty<int> Id { get; }
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public ObjectModel()
        {
            Id = new ReactiveProperty<int>();
            Name = new ReactiveProperty<string>();
            IsVisible = new ReactiveProperty<bool>();
            IsVisible.Subscribe(VisibleChanged);
        }

        private void VisibleChanged(bool b)
        {
            OpenGLPresenter.Instance.Update(MainModel.Instance.Repository);
            OpenGLPresenter.Instance.Render();
            //System.Diagnostics.Debug.Write(b.ToString());
        }
    }

}
