﻿using PG.Core.Math;
using PG.Core.Shape;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        private Sphere3d sphere;

        private int count;

        public int Count
        {
            get { return count; }
            set { this.SetProperty(ref count, value); }
        }

        public class ExecuteCommandImpl : ICommand
        {
            private SphereGenerationViewModel viewModel;

            public ExecuteCommandImpl(SphereGenerationViewModel vm)
            {
                this.viewModel = vm;
            }

            public event EventHandler CanExecuteChanged
            {
                add { }
                remove { }
            }

            public bool CanExecute(object parameter)
            {
                return true;
            }

            public void Execute(object parameter)
            {
                var random = new System.Random();
                var positions = new List<Vector3d>();
                for (int i = 0; i < viewModel.Count; ++i) {
                    var theta = random.NextDouble() * 2.0 * System.Math.PI;
                    var phi = random.NextDouble() * System.Math.PI;
                    var pos = viewModel.sphere.GetPositionByAngle(theta, phi);
                    positions.Add(pos);
                }
                var particles = new PG.Core.Shape.ParticleSystem(positions);
                //var builder = new ParticleSystemBuilder();
                //builder.Build()
            }
        }
    }
}
