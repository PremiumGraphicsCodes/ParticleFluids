using PG.Core.Shape;
using PG.Core.UI;
using System.Collections.ObjectModel;

namespace PG.CGStudio
{
    public class ObjectRepository
    {
        private PG.CLI.ObjectRepositoryAdapter adapter;

        public PG.CLI.ObjectRepositoryAdapter Adapter { get { return adapter; } }

        public ObservableCollection<ObjectModel> Objects { get; }

        public ObjectRepository(PG.CLI.ObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
            this.Objects = new ObservableCollection<ObjectModel>();
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

        public void Sync()
        {
            this.Objects.Clear();
            var ids = adapter.GetAllIds();
            foreach(var id in ids)
            {
                var item = new ObjectModel();
                item.Id.Value = id;
                item.IsVisible.Value = adapter.GetVisibleById(id);
                item.Name.Value = adapter.GetNameById(id);
                this.Objects.Add(item);
            }
        }
    }
}
