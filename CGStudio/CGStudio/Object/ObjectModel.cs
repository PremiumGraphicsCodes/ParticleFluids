using Prism.Mvvm;
using Reactive.Bindings;
using System;

namespace PG.CGStudio
{
    public class ObjectModel : BindableBase
    {
        private readonly PG.CLI.ObjectAdapter Adapter;

        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public ReactiveProperty<bool> IsSelected { get; }

        public ObjectModel(PG.CLI.ObjectAdapter adapter)
        {
            Adapter = adapter;
            Id = new ReactiveProperty<int>(adapter.GetId());
            Name = new ReactiveProperty<string>(adapter.GetName());
            IsVisible = new ReactiveProperty<bool>(adapter.GetVisible());
            IsVisible.Subscribe(OnVisibleChanged);
            IsSelected = new ReactiveProperty<bool>();
        }

        private void OnNameChanged(string str)
        {
            Adapter.SetName(str);
        }

        private void OnVisibleChanged(bool b)
        {
            Adapter.SetVisible(b);
            OpenGLPresenter.Instance.Update(MainModel.Instance.Repository);
            OpenGLPresenter.Instance.Render();
            //System.Diagnostics.Debug.Write(b.ToString());
        }
    }

}
