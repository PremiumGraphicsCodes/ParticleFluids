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
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.IsVisible = new ReactiveProperty<bool>(false);
        }
    }
}
