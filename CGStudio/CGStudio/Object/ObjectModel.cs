using Prism.Mvvm;
using Reactive.Bindings;
using System;

namespace PG.CGStudio
{
    public class ObjectModel : BindableBase
    {
        private readonly PG.CLI.ObjectAdapter adapter;

        public ReactiveProperty<int> Id { get; }
        public ReactiveProperty<string> Name { get; }
        public ReactiveProperty<bool> IsVisible { get; }

        public ObjectModel(PG.CLI.ObjectAdapter adapter)
        {
            this.adapter = adapter;
            Id = new ReactiveProperty<int>(adapter.GetId());
            Name = new ReactiveProperty<string>(adapter.GetName());
            IsVisible = new ReactiveProperty<bool>(adapter.GetVisible());
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
