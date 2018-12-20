﻿using PG.Core.Shape;

namespace PG.CGStudio
{
    public class MainModel
    {
        private PG.CLI.Model adapter;

        static MainModel instance;

        public static MainModel Instance { get { return instance; } }

        public PG.CLI.Model Adapter { get { return adapter; } }

        public MainModel()
        {
            adapter = new PG.CLI.Model();
            instance = this;
        }

        public int Add(ParticleSystem particleSystem)
        {
            return adapter.AddParticleSystem(particleSystem);
        }

        public int Add(WireFrame wireFrame)
        {
            return adapter.AddWireFrame(wireFrame);
        }

        public int Add(PolygonMesh polygonMesh)
        {
            return adapter.AddPolygonMesh(polygonMesh);
        }
    }
}
