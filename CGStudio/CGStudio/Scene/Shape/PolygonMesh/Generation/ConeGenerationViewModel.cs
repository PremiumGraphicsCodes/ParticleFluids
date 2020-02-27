using PG.Control.Math;
using PG.Core.Shape;
using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Scene.Shape.PolygonMesh.Generation
{
    public class ConeGenerationViewModel
    {
        public Cone3dViewModel ConeViewModel { get; }
            = new Cone3dViewModel();

        public ReactiveProperty<int> UNum { get; }
            = new ReactiveProperty<int>(12);

        public ReactiveCommand GenerationCommand { get; }
            = new ReactiveCommand();

        public ConeGenerationViewModel()
        {
            GenerationCommand.Subscribe(OnGenerate);
        }

        private void OnGenerate()
        {
            var builder = new PolygonMeshBuilder();
//            builder.Add(ConeViewModel.Value, UNum.Value);
        }
    }
}
