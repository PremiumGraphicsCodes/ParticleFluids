using PG.Control;
using PG.Core.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace PG.CGStudio.Generation.ParticleSystem
{
    public class SphereGenerationCommand : ICommand
    {
        private Sphere3dViewModel viewModel;

        public SphereGenerationCommand(Sphere3dViewModel vm)
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
            var sphere = viewModel.Sphere;
            for (int i = 0; i < viewModel.Count; ++i)
            {
                var theta = random.NextDouble() * 2.0 * System.Math.PI;
                var phi = random.NextDouble() * System.Math.PI;
                var pos = sphere.GetPositionByAngle(theta, phi);
                positions.Add(pos);
            }
            var particles = new PG.Core.Shape.ParticleSystem(positions);
            MainModel.Instance.Add(particles);
            //var builder = new ParticleSystemBuilder();
            //builder.Build()
        }
    }

}
