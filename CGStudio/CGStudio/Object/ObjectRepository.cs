using PG.Core.Shape;
using PG.Core.UI;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace PG.CGStudio
{
    public class ObjectRepository
    {
        private PG.CLI.ObjectRepositoryAdapter adapter;

        public PG.CLI.ObjectRepositoryAdapter Adapter { get { return adapter; } }

        public ReactiveCollection<ObjectModel> Objects { get; }

        public ObjectRepository(PG.CLI.ObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
            this.Objects = new ReactiveCollection<ObjectModel>();
        }

        public int Add(ParticleSystem particleSystem, ParticleAppearance appearance, System.String name)
        {
            var id = adapter.AddParticleSystem(particleSystem, appearance, name);
            Sync();
            return id;
        }

        public int Add(WireFrame wireFrame, WireAppearance appearance, System.String name)
        {
            var id = adapter.AddWireFrame(wireFrame, appearance, name);
            Sync();
            return id;
        }

        public int Add(PolygonMesh polygonMesh, System.String name)
        {
            var id = adapter.AddPolygonMesh(polygonMesh, name);
            Sync();
            return id;
        }

        public void Clear()
        {
            Objects.Clear();
            adapter.Clear();
        }

        public void Sync()
        {
            this.Objects.Clear();
            var objects = adapter.GetObjects();
            foreach(var o in objects)
            {
                var item = new ObjectModel(o);
                this.Objects.Add(item);
            }
        }

        public ObjectModel FindObjectById(int id)
        {
            return Objects.FirstOrDefault(x => x.Id.Value == id);
        }
    }
}
