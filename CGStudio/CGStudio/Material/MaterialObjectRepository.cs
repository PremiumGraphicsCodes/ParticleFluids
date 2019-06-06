using System.Collections.ObjectModel;

namespace PG.CGStudio.Material
{
    public class MaterialObjectRepository
    {
        private PG.CLI.MaterialObjectRepositoryAdapter adapter;

        public ObservableCollection<MaterialModel> Items;

        public MaterialObjectRepository()
        {
            this.adapter = new PG.CLI.MaterialObjectRepositoryAdapter();
            this.Items = new ObservableCollection<MaterialModel>();

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
        }

        public int Add(PG.Core.Graphics.Material material)
        {
            return this.adapter.Add(material);
        }
    }
}
