using PG.Core.Shape;
using PG.Core.UI;
using System.Collections.ObjectModel;

namespace PG.CGStudio
{
    public class ObjectRepository
    {
        private PG.CLI.ObjectRepositoryAdapter adapter;

        public PG.CLI.ObjectRepositoryAdapter Adapter { get { return adapter; } }

        public ObservableCollection<ObjectItem> Items { get; }

        public ObjectRepository(PG.CLI.ObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
            this.Items = new ObservableCollection<ObjectItem>();
        }

        public int Add(ParticleSystem particleSystem, ParticleAppearance appearance, System.String name)
        {
            var id = adapter.AddParticleSystem(particleSystem, appearance, name);
            if(id > 0)
            {
                UpdateItems();
            }
            return id;
        }

        public int Add(WireFrame wireFrame, WireAppearance appearance, System.String name)
        {
            return adapter.AddWireFrame(wireFrame, appearance, name);
        }

        public int Add(PolygonMesh polygonMesh, System.String name)
        {
            return adapter.AddPolygonMesh(polygonMesh, name);
        }

        public void UpdateItems()
        {
            this.Items.Clear();
            var ids = adapter.GetAllIds();
            foreach(var id in ids)
            {
                var item = new ObjectItem();
                item.IsVisible.Value = false;
                item.Name.Value = adapter.GetNameById(id);
                this.Items.Add(item);
            }
        }
    }
}
