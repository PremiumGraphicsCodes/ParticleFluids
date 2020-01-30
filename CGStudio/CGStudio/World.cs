﻿using PG.Scene;

namespace PG.CGStudio
{
    public class World
    {
        private PG.CLI.WorldAdapter adapter;
        public PG.CLI.WorldAdapter Adapter { get { return adapter; } }

        public SceneListModel Scenes { get; }

        public World()
        {
            this.adapter = new PG.CLI.WorldAdapter();
            this.Scenes = new SceneListModel(adapter);
        }

        public void New()
        {
            var command = new PG.CLI.Command(NewLabels.CommandNameLabel);

            Canvas3d.Instance.Renderer.Bind();
            command.Execute(adapter);
            Canvas3d.Instance.Renderer.UnBind();

            this.Scenes.Sync();
        }

        public bool Open(string filename)
        {
            return false;
        }

        public bool Save(string filename)
        {
            return false;
        }

    }
}
