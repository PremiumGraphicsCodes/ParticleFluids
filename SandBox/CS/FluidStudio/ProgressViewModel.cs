using Reactive.Bindings;

namespace FluidStudio
{
    public class ProgressViewModel
    {
        public ReactiveProperty<int> Min { get; }
            = new ReactiveProperty<int>(0);

        public ReactiveProperty<int> Max { get; }
            = new ReactiveProperty<int>(100);

        public ReactiveProperty<int> Value { get; }
            = new ReactiveProperty<int>(0);

        public ProgressViewModel()
        {
//            this.Value.Value = 50;
        }
    }
}
