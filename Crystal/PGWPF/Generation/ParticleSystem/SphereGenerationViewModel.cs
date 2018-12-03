using PG.Core.Math;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Windows.Input;
using PG.Control;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationViewModel : BindableBase
    {
        private Sphere3dViewModel sphereViewModel;

        private int count;

        public Sphere3dViewModel SphereViewModel
        {
            get {return sphereViewModel; }
        }

        public int Count
        {
            get { return count; }
            set { this.SetProperty(ref count, value); }
        }

        public SphereGenerationViewModel()
        {
            this.sphereViewModel = new Sphere3dViewModel();
            this.count = 10000;
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
                    var pos = viewModel.sphereViewModel.Sphere.GetPositionByAngle(theta, phi);
                    positions.Add(pos);
                }
                var particles = new PG.Core.Shape.ParticleSystem(positions);
                //var builder = new ParticleSystemBuilder();
                //builder.Build()
            }
        }
    }
}
