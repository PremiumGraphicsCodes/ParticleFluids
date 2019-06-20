using PG.Core.Math;
using PG.Core.Shape;
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

        public ShapeType Type
        {
            get { return Adapter.GetType(); }
        }

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
            Canvas3d.Instance.Update(MainModel.Instance.Repository);
            Canvas3d.Instance.Render();
            //System.Diagnostics.Debug.Write(b.ToString());
        }

        public void Move(Vector3d v)
        {
            Adapter.Move(v);
        }

        public void Transform(Matrix3d m)
        {
            Adapter.Transform(m);
        }

        public void Transform(Matrix4d m)
        {
            Adapter.Transform(m);
        }

        public Vector3d GetPosition(int id)
        {
            return Adapter.GetPositionById(id);
        }

    }
}
