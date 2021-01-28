﻿using FluidStudio.Physics.Fluid;
using Microsoft.Win32;
using PG.CGStudio.UICtrl;
using PG.Control.OpenGL;
using PG.Control.UI;
using PG.Scene;
using Prism.Mvvm;
using Prism.Regions;
using Reactive.Bindings;
using System;
using System.Linq;

namespace FluidStudio.Physics
{
    public class FluidSceneViewModel : INavigationAware
    {
        public ReactiveProperty<string> Name { get; }
            = new ReactiveProperty<string>("Fluid01");

        //public SceneSelectViewModel SourceParticleSystemSelectViewModel { get; }

        public ReactiveCommand ParticleFileSelectCommand { get; }
            = new ReactiveCommand();

        public ReactiveProperty<string> ParticleFilePath { get; }
            = new ReactiveProperty<string>("");

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

        public ReactiveCommand UpdateCommand { get; }
            = new ReactiveCommand();

        private FluidScene scene;

        private SceneList world;

        private MainModel mainModel;

        private Canvas3d canvas;

        private int particleSystemId;

        public FluidSceneViewModel(MainModel model, SceneList world, Canvas3d canvas)
        {
            this.mainModel = model;
            this.canvas = canvas;
            this.ParticleFileSelectCommand.Subscribe(OnSelectPSFile);
//            this.ParticleFileSelectCommand = new
            //this.SourceParticleSystemSelectViewModel = new SceneSelectViewModel(world, canvas);
            this.world = world;
            this.UpdateCommand.Subscribe(OnUpdate);
        }

        private void OnSelectPSFile()
        {
            var dialog = new OpenFileDialog()
            {
                Title = "Import",
                Filter = "OpenVDBFile(*.vdb)|*.vdb|AllFiles(*.*)|*.*",
            };
            if (dialog.ShowDialog() == true) {
                this.ParticleFilePath.Value = dialog.FileName;
                var ids = mainModel.VDBModel.Read(this.ParticleFilePath.Value, world);
                if(ids.Count() > 0)
                {
                    this.particleSystemId = ids[0];
                    canvas.BuildShader(world, this.particleSystemId);
                    canvas.Render();
                }
            }
        }

        public void OnNavigatedTo(NavigationContext navigationContext)
        {
            var item = navigationContext.Parameters["Scene"] as FluidScene;
            if (item == null)
            {
                return;
            }
            this.Id.Value = item.Id;
            this.Name.Value = item.Name;
            this.particleSystemId = item.SourceParticleSystemId;
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

        private void OnUpdate()
        {
            if (scene == null)
            {
                return;
            }
            //var sourceId = SourceParticleSystemSelectViewModel.Id.Value;
            
            var density = Density.Value;
            var stiffness = Stiffness.Value;
            var viscosity = Viscosity.Value;
            var name = Name.Value;
            var isBoundary = IsBoundary.Value;
            this.scene.Update(world, particleSystemId, density, stiffness, viscosity, name, isBoundary);
        }
    }
}
