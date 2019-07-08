using Reactive.Bindings;

namespace PG.CGStudio.Material
{
    public class MaterialModel
    {
        public Core.Graphics.Material Material;

        public ReactiveProperty<int> Id { get; }

        public ReactiveProperty<string> Name { get; }

        public ReactiveProperty<bool> IsVisible { get; }

        public MaterialModel()
        {
            this.Id = new ReactiveProperty<int>();
            this.Name = new ReactiveProperty<string>();
            this.IsVisible = new ReactiveProperty<bool>();

//            adapter.Update(Material);
        }
    }
}
