﻿using PG.Control.Math;
using PG.Core.Graphics;
using Prism.Mvvm;
using Reactive.Bindings;

namespace PG.Control.Graphics
{
    public class PointLightViewModel : BindableBase
    {
        public PointLightViewModel()
        {
            ID = new ReactiveProperty<int>();
            Position = new Vector3dViewModel();
            Ambient = new ColorRGBAViewModel();
            Diffuse = new ColorRGBAViewModel();
            Specular = new ColorRGBAViewModel();
        }

        public ReactiveProperty<int> ID { get; }

        public Vector3dViewModel Position { get; }

        public ColorRGBAViewModel Ambient { get; }

        public ColorRGBAViewModel Diffuse { get; }

        public ColorRGBAViewModel Specular { get; }

        public PointLight Value
        {
            set
            {
                ID.Value = value.ID;
                Position.Value = value.Position;
                Ambient.Value = value.Ambient;
                Diffuse.Value = value.Diffuset;
                Specular.Value = value.Specular;
            }
        }
    }
}
