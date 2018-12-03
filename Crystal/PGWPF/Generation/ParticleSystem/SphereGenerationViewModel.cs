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

        private GenerationCommandImpl generationCommand;

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

        public ICommand GenerationCommand
        {
            get { return generationCommand; }
        }

        public SphereGenerationViewModel()
        {
            this.sphereViewModel = new Sphere3dViewModel();
            this.count = 10000;
            this.generationCommand = new GenerationCommandImpl(this);
        }

        public class GenerationCommandImpl : ICommand
        {
            private SphereGenerationViewModel viewModel;

            public GenerationCommandImpl(SphereGenerationViewModel vm)
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
                var sphere = viewModel.sphereViewModel.Sphere;
                for (int i = 0; i < viewModel.Count; ++i) {
                    var theta = random.NextDouble() * 2.0 * System.Math.PI;
                    var phi = random.NextDouble() * System.Math.PI;
                    var pos = viewModel.sphereViewModel.Sphere.GetPositionByAngle(theta, phi);
                    positions.Add(pos);
                }
                var particles = new PG.Core.Shape.ParticleSystem(positions);
                MainModel.Instance.Add(particles);
                //var builder = new ParticleSystemBuilder();
                //builder.Build()
            }
        }
    }
}
