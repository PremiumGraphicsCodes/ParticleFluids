using Reactive.Bindings;

namespace PG.CGStudio.Material
{
    public class MaterialModel
    {
        private readonly CLI.MaterialObjectAdapter adapter;

        public Core.Graphics.Material Material;

        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public MaterialModel(CLI.MaterialObjectAdapter adapter)
        {
            this.adapter = adapter;
            this.Id = new ReactiveProperty<int>(adapter.GetId());
            this.Name = new ReactiveProperty<string>(adapter.GetName());
            this.IsVisible = new ReactiveProperty<bool>(adapter.GetVisible());

            this.Material = adapter.GetValue();
//            adapter.Update(Material);
        }

        public void Sync()
        {
            adapter.Update(Material);
        }
    }
}
