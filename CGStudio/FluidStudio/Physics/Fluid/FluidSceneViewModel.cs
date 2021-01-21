using FluidStudio.Physics.Fluid;
using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;

namespace FluidStudio.Physics
{
    public class FluidSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Fluid01");

        public SceneSelectViewModel SourceParticleSystemSelectViewModel { get; }

        public ReactiveProperty<int> Id { get; }
            = new ReactiveProperty<int>();

        public ReactiveProperty<float> Density { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Stiffness { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<float> Viscosity { get; }
            = new ReactiveProperty<float>(1.0f);

        public ReactiveProperty<bool> IsBoundary { get; }
            = new ReactiveProperty<bool>(false);

        public FluidFileExportViewModel ExportViewModel { get; }
            = new FluidFileExportViewModel();

        private FluidScene scene;

        private SceneList world;

        public FluidSceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.SourceParticleSystemSelectViewModel = new SceneSelectViewModel(world, canvas);
            this.SourceParticleSystemSelectViewModel.Id.Subscribe(OnChangeSourcePS);
            this.Density.Subscribe(OnChangeDensity);
            this.Stiffness.Subscribe(OnChangeStiffness);
            this.IsBoundary.Subscribe(OnChangeIsBoundary);
            this.world = world;
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as FluidScene;
            if (item == null)
            {
                return;
            }
            this.Id.Value = item.Id;
            this.SourceParticleSystemSelectViewModel.Id.Value = item.SourceParticleSystemId;
            this.Density.Value = item.Density;
            this.Stiffness.Value = item.Stiffness;
            this.Viscosity.Value = item.Viscosity;
            this.IsBoundary.Value = item.IsBoundary;
            this.ExportViewModel.Model = item.ExportModel;
            this.scene = item;
        }

        public bool IsNavigationTarget(NavigationContext navigationContext)
        {
            return true;
        }

        public void OnNavigatedFrom(NavigationContext navigationContext)
        {
        }

        private void OnChangeSourcePS(int id)
        {
            OnUpdate();
        }

        private void OnChangeDensity(float density)
        {
            OnUpdate();
        }

        private void OnChangeStiffness(float s)
        {
            OnUpdate();
        }

        private void OnChangeViscosity(float v)
        {
            OnUpdate();
        }

        private void OnChangeIsBoundary(bool b)
        {
            OnUpdate();
        }

        private void OnUpdate()
        {
            if (scene == null)
            {
                return;
            }
            var sourceId = SourceParticleSystemSelectViewModel.Id.Value;
            var density = Density.Value;
            var stiffness = Stiffness.Value;
            var viscosity = Viscosity.Value;
            var name = Name.Value;
            var isBoundary = IsBoundary.Value;
            this.scene.Update(world, sourceId, density, stiffness, viscosity, name, isBoundary);
        }
    }
}
