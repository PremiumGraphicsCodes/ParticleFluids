using System.Collections.ObjectModel;

namespace PG.CGStudio.Material
{
    public class MaterialObjectRepository
    {
        private PG.CLI.MaterialObjectRepositoryAdapter adapter;

        public ObservableCollection<MaterialModel> Items;

        public MaterialObjectRepository(PG.CLI.MaterialObjectRepositoryAdapter adapter)
        {
            this.adapter = adapter;
            this.Items = new ObservableCollection<MaterialModel>();

            Add(new PG.Core.Graphics.Material(), "Mat1");
            Add(new PG.Core.Graphics.Material(), "Mat2");

            /*
            var item1 = new MaterialModel(1);
            item1.Name.Value = "Material1";
            item1.IsVisible.Value = true;
            var item2 = new MaterialModel(2);
            item2.Name.Value = "Material2";
            item2.IsVisible.Value = false;
            Items.Add(item1);
            Items.Add(item2);
            */
            Sync();

        }

        public int Add(PG.Core.Graphics.Material material, string name)
        {
            return this.adapter.Add(material, name);
        }

        public void Sync()
        {
            this.Items.Clear();
            var objects = adapter.GetObjects();
            foreach (var o in objects)
            {
                var item = new MaterialModel(o);
                this.Items.Add(item);
            }
        }
    }
}
